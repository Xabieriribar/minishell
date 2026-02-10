#include "minishell.h"

char	*ft_type_to_str(t_token *lst)
{
	if (lst->type == T_HEREDOC)
		return ("<<");
	else if (lst->type == T_REDIR_APPEND)
		return (">>");
	return (lst->value);
}
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

int find_number_of_redirs(t_token *token_list)
{
	int number_of_redirs;

	if (!token_list)
		return (-1);
	number_of_redirs = 0;
	while (token_list)
	{
		if (ft_is_redir(token_list->type) == 0)
			number_of_redirs++;
		token_list = token_list->next;
	}
	return (number_of_redirs);
}

void	ft_lstadd_back_redirs(t_redirs **lst, t_redirs *new)
{
	t_redirs *ptr;

	ptr = ft_lstlast_redirs(*lst);
	if (!ptr)
		*lst = new;
	else
		ptr->next = new;
}

t_redirs *ft_lstlast_redirs(t_redirs *lst)
{
	t_redirs *ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

t_redirs *ft_lstnew_redirs(char *filename, t_type redir_type)
{
	t_redirs *li;

	li = malloc(sizeof(struct s_redirs));
	if (!li)
		return (NULL);
	li->filename = filename;
	li->redir_type = redir_type;
	li->next = NULL;
	return (li);
}