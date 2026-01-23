/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:40:25 by rick              #+#    #+#             */
/*   Updated: 2026/01/21 18:54:06 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- All this functions will create a string according to the string
- recieved, separating like this all the different cases.

+ Words (normal characters)
+ Single quotes '...' (literal text)
+ Double quotes "..." (literal text, allows $ later)
+ Pipes |
+ Input redirection <
+ Output redirection >
+ Heredoc <<
+ Append redirection >>
+ Syntax error on unclosed quotes */

/* 
* This function creates the linked list of tokens
* also setting up their indexes and value.
+ The return value is a pointer to the first element of the list */
// --------- VER INDICES EN VEZ DE PUNTEROS EN STR ITERERATION ------/
t_token	*init_list(char *str)
{
	t_token	*head;
	int		token_number;
	int		len;

	token_number = 0;
	head = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		while (is_space(*str))
			str++;
		if (!*str)
			break ;
		len = init_add_token(&head, str, token_number);
		if (len < 0)
			return (perror("Failed token creation"), free_tokens(&head), NULL);
		else
			str += len;
		token_number++;
	}
	set_types(&head);
	set_dolar(&head);
	return (head);
}

/*
* Helper function, runs the token creation function for each case.
+ Returns the length of the sring "value" created in that node
+ or a negative interger for error.*/
int	init_add_token(t_token **head, char *str, int ix)
{
	if (is_operator(*str))
		return (token_operator(head, str, ix));
	else if (is_double(*str))
		return (token_double(head, str, ix));
	else if (is_single(*str))
		return (token_single(head, str, ix));
	else
		return (token_word(head, str, ix));
}
