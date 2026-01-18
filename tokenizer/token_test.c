/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:26:09 by rick              #+#    #+#             */
/*   Updated: 2026/01/18 17:31:44 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*type_to_str(t_type type)
{
	if (type == T_WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_REDIR_IN)
		return ("REDIR_IN");
	if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	if (type == T_REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == T_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}

// Function to print a single token
static void	print_token(t_token *token)
{
	if (!token)
		return ;
	printf("Index: %d | Type: %s | Value: '%s'\n",
		token->index,
		type_to_str(token->type),
		token->value);
}

// Function to print the entire linked list
static void	print_token_list(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		print_token(current);
		current = current->next;
	}
}

// Test function
void	test_init_list(char *line)
{
	t_token	*head;

	head = init_list(line);
	if (!head)
	{
		printf("Failed to initialize token list.\n");
		return ;
	}
	printf("Token list:\n");
	print_token_list(head);
	free_tokens(&head);
}
