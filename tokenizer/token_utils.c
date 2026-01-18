/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:20:03 by rick              #+#    #+#             */
/*   Updated: 2026/01/18 14:22:37 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Adds a token to the last position of the list*/
void	lst_add_back_token(t_token **lst, t_token *new)
{
	t_token	*ptr;

	ptr = ft_lstlast(*lst);
	if (!ptr)
		*lst = new;
	else
		ptr->next = new;
}

/* 
* Returns a pointer to the last element of the list */
t_token	*lstlast_token(t_token *lst)
{
	t_token	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

/* 
* Frees a linked list of tokens the char *value 
* from each node. */
void	free_tokens(t_token **head)
{
	t_token	*poanteg;

	poanteg = *head;
	while (poanteg->next)
	{
		poanteg = lstlast_token(*head);
		free(poanteg->value);
		free(poanteg);
		poanteg = *head;
	}
	free(poanteg->value);
	free(poanteg);
}

void	free_split(char **split)
{
	int	i;

	i = 0;

	if (!split)
		return;

	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
