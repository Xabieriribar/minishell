#include "minishell.h"
int execute_heredoc(int fd_heredoc, char *delimiter)
{
    char *line;

    line = NULL;
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
            break ;
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
        {
            free(line);
            break ;
        }
        write(fd_heredoc, line, ft_strlen(line));
        write(fd_heredoc, "\n", 1);
        free(line);
    }
    close(fd_heredoc);
    return (0);
}
void    search_and_execute_heredoc(t_redirs *redirs, int *heredoc_file_index)
{
    t_redirs *temp_redir;
    int     fd_heredoc;
    char    *num_str;

    temp_redir = redirs;
    while (temp_redir)
    {
        if (temp_redir->redir_type == T_HEREDOC)
        {
            num_str = ft_itoa(*heredoc_file_index);
            temp_redir->temp_heredoc_filename = ft_strjoin("/tmp/.heredoc_", num_str);
            free(num_str);
            fd_heredoc = open(temp_redir->temp_heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_heredoc < 0)
                perror("Open for the heredoc failed");
            execute_heredoc(fd_heredoc, temp_redir->filename);
            *heredoc_file_index += 1;
        }
        temp_redir->filename = temp_redir->temp_heredoc_filename;
        temp_redir = temp_redir->next;
    }
}
int     contains_heredoc_redirs(t_redirs *redirs)
{
    while (redirs)
    {
        if (redirs->redir_type == T_HEREDOC)
            return (1);
        redirs = redirs->next;
    }
    return (0);
}
void    open_temporary_heredocs(t_node *tree, int *heredoc_file_index)
{
    if (!tree)
        return ;
    if (tree->node_type == COMMAND)
    {
        if (tree->redirs != NULL && contains_heredoc_redirs(tree->redirs))
            search_and_execute_heredoc(tree->redirs, heredoc_file_index);
        return ;
    }
    open_temporary_heredocs(tree->left_child, heredoc_file_index);
    open_temporary_heredocs(tree->right_child, heredoc_file_index);
    return ;
}