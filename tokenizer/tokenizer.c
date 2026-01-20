/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:42:41 by rick              #+#    #+#             */
/*   Updated: 2026/01/20 11:50:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
+ TOKENIZER:
- It scans the input one character at a time,
- building tokens, and only split tokens when 
- the shell grammar says it's allowed to.
*/

/* 
* This function creates the linked list of tokens
* also setting up their indexes and value.
+ The return value is a pointer to the first element of the list */
t_token	*init_list(char *str)
{
	t_token	*head;
	int		i;
	char	*value;

	i = 0;
	head = NULL;
	value = get_value(str);
	init_add_token(&head, value);
	if (!head)
		return (NULL);
	i++;
	while (*str)
	{
		if (init_add_token(&head, value) == 0)
			return (free_tokens(&head), NULL);
		i++;
	}
	return (head);
}

/* 
* This function initializes a token and adds it to the 
* end of the list.
* Allocates memory and sets its index and value.
+ Return 1 on succes or 0 on error.*/
int	init_add_token(t_token **head, char *str)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (0);
	token->value = ft_strdup(str);
	if (!token->value)
		return (0);
	token->index = 0;
	token->type = T_WORD;
	token->next = NULL;
	lst_add_back_token(head, token);
	return (1);
}

char	*concat_char(char *str, char c)
{
	char	*new;
	int		i;

	if (!str)
	{
		new = ft_calloc(sizeof(char), 2);
		if (!new)
			return (NULL);
		new[0] = c;
		return (new);
	}
	new = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!new)
		return (NULL);
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	return (free(str), new);
}

bool	is_single(char c)
{
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_double(char c)
{
	if (c == '\"')
		return (true);
	return (false);
}

bool	is_space(int c)
{
	if (c == ' ' ||
		c == '\n' ||
		c == '\t' ||
		c == '\v' ||
		c == '\f' ||
		c == '\r')
		return (true);
	return (false);
}

bool	is_operator(char *str)
{
	if (!ft_strncmp(str, "|", 1) ||
		!ft_strncmp(str, "<", 1) ||
		!ft_strncmp(str, ">", 1))
		return (true);
	return (false);
}

if (is_space(*str))
{
	str++;
	continue ;
}
else if (is_operator)
	str += make_operator(head, str);
else if (is_double)
	str += make_double(head, str);
else if (is_single)
	str += make_single(head, str);
else
	str += make_word(head, str);