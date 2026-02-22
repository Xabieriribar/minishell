#include "minishell.h"

void    update_fd(t_redirs *redirs, int *fd_in, int *fd_out, int flag)
{
    while (redirs)
    {
        if (redirs->redir_type == T_REDIR_IN || redirs->redir_type == T_HEREDOC)
        {
            if (*fd_in != 0)
                close(*fd_in);
            *fd_in = open(redirs->filename, O_RDONLY, 0644);
            if (*fd_in < 0)
            {
                if (flag)
                    return ;
                write_error_message(redirs->filename);
                ft_putstr_fd(": No such file or directory\n", 2);
                exit(EXIT_FAILURE);
            }
        }
        else if (redirs->redir_type == T_REDIR_OUT || redirs->redir_type == T_REDIR_APPEND)
        {
            if (*fd_out != 1)                close(*fd_out);
            
            if (redirs->redir_type == T_REDIR_OUT)
                *fd_out = open(redirs->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else
                *fd_out = open(redirs->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            
            if (*fd_out < 0)
            {
                if (flag)
                    return ;
                write_error_message(redirs->filename);
                ft_putstr_fd("No such file or directory\n", 2);
                exit(EXIT_FAILURE);
            }
        }
        redirs = redirs->next;
    }
}