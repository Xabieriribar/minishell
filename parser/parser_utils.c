#include "minishell.h"

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
    printf("Lstsize is %d\n", i);
	return (i);
}