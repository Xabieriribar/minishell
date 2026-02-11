/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:20:03 by rick              #+#    #+#             */
/*   Updated: 2026/02/11 17:22:25 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Adds a token to the last position of the list*/
void	lst_add_back_token(t_token **lst, t_token *new)
{
	t_token	*ptr;

	if (!new)
		return ;
	new->next = NULL;
	new->prev = NULL;
	ptr = lstlast_token(*lst);
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	ptr->next = new;
	new->prev = ptr;
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
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free((*head)->value);
		free(*head);
		*head = tmp;
	}
}

/* 
* Funtion to set the enum types for a token in the list.
+ T_PIPE → |
+ T_REDIR_IN → <
+ T_REDIR_OUT → >
+ T_REDIR_APPEND → >>
+ T_HEREDOC → << */
void	set_type(t_token *token, char *str)
{
	if (!ft_strncmp(str, ">>", 2))
		token->type = T_REDIR_APPEND;
	else if (!ft_strncmp(str, "<<", 2))
		token->type = T_HEREDOC;
	else if (!ft_strncmp(str, "|", 1))
		token->type = T_PIPE;
	else if (!ft_strncmp(str, "<", 1))
		token->type = T_REDIR_IN;
	else if (!ft_strncmp(str, ">", 1))
		token->type = T_REDIR_OUT;
	else
		token->type = T_WORD;
}

/* 
* Funtion to set the int dolar on tokens.
+ In function token_single(), the dolar value will be set inmediatly
+ to -1, so we never mark it as true in that case.
+ Otherwise the value will be 1 for true, and 0 for false.*/
void	set_dolar(t_token *token)
{
	if (token->dolar == -1)
		return ;
	else if (token->type == T_WORD
		&& ft_strchr(token->value, '$') != NULL
		&& ft_strlen(token->value) > 1)
		token->dolar = 1;
	else
		token->dolar = 0;
}
