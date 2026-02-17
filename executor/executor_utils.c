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
int     contains_slash(char *suspect)
{
    int i;

    i = 0;
    while (suspect[i])
    {
        if (suspect[i] == '/')
            return (1);
        i++;
    }
    return (0);
}

void    close_if_not_stdin_or_stdout(int fd_in, int fd_out)
{
    if (fd_in != 0)
        close(fd_in);
    if (fd_out != 1)
        close(fd_out);
}

char    *can_access(char *command, char *result)
{
    if (access(command, F_OK | X_OK) == -1)
        return (NULL);
    result = ft_strdup(command);
    return (result);
}