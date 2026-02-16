
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
            updated_fd_in = open(redirs->filename, O_RDONLY)
        }
    }

}
/*THIS FUNCTION MUST BE CALLED BEFORE EXECUTE_PIPELINE IS CALLED. WHY? WE MUST FILL THE TEMPORARY
FILE DESCRIPTOR OF HEREDOC WHEN FINDING IT, LIKE THIS, WE DONT OVERCOMPLICATE OUR LIFE ON THE MAIN
EXECUTOR*/

int open_temporary_heredocs(t_node *tree, int *heredoc_file_index)
{
    if ()

}
int execute_pipeline(t_node *tree, int fd_in, int fd_out, int *pid_count, int *pid_values)
{
    pid_t   process_id;
    int     pipefdes[2];
    char    *pathname;
    int     call_fork_twice;
    int     pid_temp_index;

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
            dup2(fd_in, 0);
            dup2(fd_out, 1);
            // pathname = search_path();
            // execve()
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
    }

}