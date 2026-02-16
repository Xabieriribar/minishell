#include "minishell.h"

int contains_out_redirs(t_redirs *redirs)
{
    while (redirs)
    {
        if (redirs->redir_type ==  T_REDIR_OUT || redirs->redir_type == T_REDIR_APPEND)
            return (1);
        redirs = redirs->next;
    }
    return (0);
}

int contains_in_redirs(t_redirs *redirs)
{
    while (redirs)
    {
        if (redirs->redir_type ==  T_REDIR_IN || redirs->redir_type == T_HEREDOC)
            return (1);
        redirs = redirs->next;
    }
    return (0);
}

int update_fd_out(t_redirs *redirs)
{
    int updated_fd_out;
    int out_count;

    out_count = 0;
    updated_fd_out = 0;
    while (redirs)
    {
        if (redirs->redir_type == T_REDIR_OUT)
        {
            if (out_count > 0)
                close(update_fd_out);
            updated_fd_out = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC);
            if (updated_fd_out < 0)
                perror("Open failed when input redirections");
        }
        if (redirs->redir_type == T_REDIR_APPEND)
        {
            if (out_count > 0)
                close(update_fd_out);
            updated_fd_out = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND);
            if (updated_fd_out < 0)
                perror("Open failed when output redirections");
        }
        out_count++;
        redirs = redirs->next;
    }
    return 0;
}
int update_fd_in(t_redirs *redirs)
{
    int updated_fd_in;
    int in_count;

    in_count = 0;
    updated_fd_in = 0;
    while (redirs)
    {
        if (redirs->redir_type == T_REDIR_IN || redirs->redir_type == T_HEREDOC)
        {
            if (in_count > 0)
                close(update_fd_in);
            updated_fd_in = open(redirs->filename, O_RDONLY);
            if (updated_fd_in < 0)
                perror("Open failed when input redirections");
        }
        in_count++;
        redirs = redirs->next;
    }
    return 0;
}

int execute_heredoc(int fd_heredoc, char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline(">");
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
/*THIS FUNCTION MUST BE CALLED BEFORE EXECUTE_PIPELINE IS CALLED. WHY? WE MUST FILL THE TEMPORARY
FILE DESCRIPTOR OF HEREDOC WHEN FINDING IT, LIKE THIS, WE DONT OVERCOMPLICATE OUR LIFE ON THE MAIN
EXECUTOR*/
int open_temporary_heredocs(t_node *tree, int *heredoc_file_index)
{
    t_redirs    *temp_redir;
    int         fd_heredoc;

    temp_redir = NULL;
    if (tree->node_type == COMMAND)
    {
        if (tree->redirs != NULL)
        {
            temp_redir = tree->redirs;
            while (temp_redir)
            {
                if (temp_redir->redir_type == T_HEREDOC)
                {
                    temp_redir->temp_heredoc_filename = ft_atoi(*heredoc_file_index);
                    temp_redir->temp_heredoc_filename = ft_strjoin("/tmp/.heredoc_", heredoc_filename);
                    fd_heredoc = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC);
                    if (fd_heredoc < 0)
                        perror("Open for the heredoc failed");
                    execute_heredoc(fd_heredoc, temp_redir->filename);
                    *heredoc_file_index++;
                }
                temp_redir->filename = temp_redir->temp_heredoc_filename;
                temp_redir = temp_redir->next;
            }
        }
        return 0;
    }
    open_temporary_heredocs(tree->left_child, heredoc_file_index);
    open_temporary_heredocs(tree->right_child, heredoc_file_index);
    return 0;
}

int execute_pipeline(t_node *tree, int fd_in, int fd_out, int *pid_count, int *pid_values)
{
    pid_t   process_id;
    int     pipefdes[2];
    // char    *pathname;
    int     pid_values[MAX_FORK];
    int     index;
    int     status;

    index = 0;
    if (tree->node_type == COMMAND)
    {
        process_id = fork();
        if (process_id == 0)
        {
            if (tree->redirs != NULL)
            {
                if (contains_in_redirs(tree->redirs))
                    fd_in = update_fd_in(tree->redirs);
                if (contains_out_redirs(tree->redirs))
                    fd_out = update_fd_out(tree->redirs);
            }
            if (fd_in != 0)
            {
                dup2(fd_in, 0);
                close(fd_in);
            }
            if (fd_out != 0)
            {
                dup2(fd_out, 1);
                close(fd_out);
            }
            // pathname = search_path();
            // execve()
            exit(1);
        }
        if (fd_in != 0)
            close(fd_in);
        if (fd_out != 1)
            close(fd_out);
        pid_values[*pid_count] = process_id;
        *pid_count++;
    }
    else
    {
        if (pipe(pipefdes) < 0)
            perror("First pipe failed to execute");
        exeucte_pipeline(tree->left_child, fd_in, pipefdes[1]);
        execute_pipeline(tree->right_child, pipefdes[0], fd_out);
        while (index < *pid_count)
        {
            waitpid(pid_values[index], &status, 0);
            if (WIFEXITED(status))
                status = WEXITSTATUS(status);
            index++;
        }
    }
    //THIS IS WHERE WE HAVE TO SAVE THE STATUS OF THE LAST CHILD INTO A LARGER DATA STRUCTURE TO NOT FUCK OURSEVES UP
    //OR JUST RETURN IT
    return (status);
}