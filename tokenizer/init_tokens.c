/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 18:19:45 by rick              #+#    #+#             */
/*   Updated: 2026/01/19 18:01:26 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* This function initializes a token and adds it to the 
* end of the list.
* Allocates memory and sets its index and value.
+ Return 1 on succes or 0 on error.*/
int	init_add_token(t_token **head, char *str, int i)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (0);
	token->value = ft_strdup(str);
	if (!token->value)
		return (0);
	token->index = i;
	token->type = T_WORD;
	token->next = NULL;
	lst_add_back_token(head, token);
	return (1);
}

/* 
* This function creates the linked list of tokens
* also setting up their indexes and value.
+ The return value is a pointer to the first element of the list */
t_token	*init_list(char *str)
{
	t_token	*head;
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	head = NULL;
	init_add_token(&head, split[i], i);
	if (!head)
		return (NULL);
	i++;
	while (split[i])
	{
		if (init_add_token(&head, split[i], i) == 0)
			return (free_split(split), free_tokens(&head), NULL);
		i++;
	}
	set_types(&head);
	return (free_split(split), head);
}

/* 
* Funtion to set the enum types for each token in the list.
+ T_PIPE → |
+ T_REDIR_IN → <
+ T_REDIR_OUT → >
+ T_REDIR_APPEND → >>
+ T_HEREDOC → << */
void	set_types(t_token **head)
{
	t_token	*poanteg;
	char	*str;

	poanteg = *head;
	while (poanteg)
	{
		str = poanteg->value;
		if (!ft_strncmp(str, "|", 1))
			poanteg->type = T_PIPE;
		if (!ft_strncmp(str, "<", 1))
			poanteg->type = T_REDIR_IN;
		if (!ft_strncmp(str, ">", 1))
			poanteg->type = T_REDIR_OUT;
		if (!ft_strncmp(str, ">>", 2))
			poanteg->type = T_REDIR_APPEND;
		if (!ft_strncmp(str, "<<", 2))
			poanteg->type = T_HEREDOC;
		poanteg = poanteg->next;
	}
}
