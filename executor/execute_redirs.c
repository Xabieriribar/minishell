#include "minishell.h"

void    open_redir_append(char *filename, int append_count, int *updated_fd_append)
{
    if (append_count > 0)
        close(*updated_fd_append);
    *updated_fd_append = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (*updated_fd_append < 0)
        perror("Error");
}

void open_redir_out(char *filename, int out_count, int *updated_fd_out)
{
    if (out_count > 0)
        close(*updated_fd_out);
    *updated_fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*updated_fd_out < 0)
        perror("Error");
}
int update_fd_out(t_redirs *redirs)
{
    int updated_fd_out;
    int out_count;
    int append_count;

    out_count = 0;
    append_count = 0;
    updated_fd_out = 0;
    while (redirs)
    {
        if (redirs->redir_type == T_REDIR_OUT)
        {
            open_redir_out(redirs->filename, out_count, &updated_fd_out);
            out_count++;
        }
        if (redirs->redir_type == T_REDIR_APPEND)
        {
            open_redir_append(redirs->filename, append_count, &updated_fd_out);
            append_count++;
        }
        redirs = redirs->next;
    }
    return (updated_fd_out);
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
                close(updated_fd_in);
            updated_fd_in = open(redirs->filename, O_RDONLY);
            if (updated_fd_in < 0)
                perror("Error");
        }
        in_count++;
        redirs = redirs->next;
    }
    return 0;
}

void    update_fd(t_redirs *redirs, int *fd_in, int *fd_out)
{
    if (contains_in_redirs(redirs))
        *fd_in = update_fd_in(redirs);
    if (contains_out_redirs(redirs))
        *fd_out = update_fd_out(redirs);
}