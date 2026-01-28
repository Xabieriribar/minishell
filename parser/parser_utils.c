#include "minishell.h"

int		ft_is_append_or_heredoc(t_type type)
{
	if (type == T_HEREDOC)
		return (1);
	else if (type == T_REDIR_APPEND)
		return (2);
	return (0);
}
int		ft_is_redir(t_type type)
{
	if (type == T_PIPE || type == T_WORD)
		return (1);
	return (0);
}

int		ft_token_lstsize(t_token *lst)
{
	int		i;
	t_token *ptr;

	if (!lst)
		return (0);
	i = 1;
	ptr = lst;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}