/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:40:25 by rick              #+#    #+#             */
/*   Updated: 2026/02/24 20:10:40 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_spaces(char **str, int *separated);

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
t_token	*init_list(char *str, t_data *data)
{
	t_token	*head;
	int		token_number;
	int		len;
	int		separated;

	token_number = 0;
	head = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		skip_spaces(&str, &separated);
		if (!*str)
			break ;
		len = init_add_token(&head, str, separated, data);
		if (len < 0)
			return (perror("Failed token creation"), free_tokens(&head), NULL);
		str += len;
		token_number++;
	}
	return (head);
}

static void	skip_spaces(char **str, int *separated)
{
	if (!str || !*str)
		return ;
	*separated = 0;
	while (**str && is_space(**str))
	{
		*separated = 1;
		(*str)++;
	}
}

static int	ft_t_lstsize(t_token *token)
{
	int		i;
	t_token	*ptr;

	if (!token)
		return (0);
	i = 1;
	ptr = token;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

/*
* Helper function, runs the token creation function for each case.
+ Returns the length of the sring "value" created in that node
+ or a negative interger for error.*/
int	init_add_token(t_token **head, char *str, int sep, t_data *data)
{
	t_token	*last;

	last = lstlast_token(*head);
	if (is_operator(*str))
		return (token_operator(head, str, ft_t_lstsize(*head)));
	if (!sep && last && last->type == T_WORD)
	{
		if (is_double(*str))
			return (token_double_append(last, str, data));
		else if (is_single(*str))
			return (token_single_append(last, str));
		else
			return (token_word_append(last, str, data));
	}
	else
	{
		if (is_double(*str))
			return (token_double(head, str, ft_t_lstsize(*head), data));
		else if (is_single(*str))
			return (token_single(head, str, ft_t_lstsize(*head)));
		else
			return (token_word(head, str, ft_t_lstsize(*head), data));
	}
}

/*
+ Simple helper function to handle flags and init values.
- Flag == 1 is a simple quote case
- Flag == 2 is a double quote or no quote case
- Flag == 3 operators.*/
void	set_init(t_token *token, char *str, int ix, int flag)
{
	set_type(token, str);
	if (flag == 1)
	{
		token->next = NULL;
		token->index = ix;
		token->hdoc_expand = false;
		token->dolar = -1;
	}
	if (flag == 2)
	{
		token->index = ix;
		if (token->prev && token->prev->type == T_HEREDOC)
			token->hdoc_expand = true;
		else
			token->hdoc_expand = false;
		token->next = NULL;
		token->index = ix;
	}
	if (flag == 3)
	{
		token->next = NULL;
		token->index = ix;
		token->hdoc_expand = false;
	}
}
