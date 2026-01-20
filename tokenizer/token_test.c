/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:26:09 by rick              #+#    #+#             */
/*   Updated: 2026/01/20 15:07:00 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*type_to_str(t_type type)
{
	if (type == T_WORD)
		return (CYAN "WORD" RESET);
	if (type == T_PIPE)
		return (YELLOW "PIPE" RESET);
	if (type == T_REDIR_IN)
		return (GREEN "REDIR_IN" RESET);
	if (type == T_REDIR_OUT)
		return (GREEN "REDIR_OUT" RESET);
	if (type == T_REDIR_APPEND)
		return (GREEN "REDIR_APPEND" RESET);
	if (type == T_HEREDOC)
		return (BLUE "HEREDOC" RESET);
	return (RED "UNKNOWN" RESET);
}

static void	print_token(t_token *token)
{
	char	*val;
	char	*dol;

	if (!token)
		return ;
	val = token->value;
	if (!val)
		val = "(null)";
	if (token->dolar == 1)
		dol = GREEN "TRUE " RESET;
	else
		dol = RED "FALSE" RESET;
	printf(" | %-5d | %-20s | %-15s | Value: '%s'\n",
		token->index, type_to_str(token->type), dol, val);
}

static void	print_token_list(t_token *head)
{
	t_token	*current;

	printf(" ____________________________________________________________\n");
	printf(" | %-5s | %-11s | %-5s | %s\n", "INDEX", "TYPE", "DOLAR", "VALUE");
	printf(" |-------|--------------|-------|----------------------------\n");
	current = head;
	while (current)
	{
		print_token(current);
		current = current->next;
	}
	printf(" ------------------------------------------------------------\n");
}

void	test_init_list(char *line)
{
	t_token	*head;

	printf("\n%s[TEST] Input:%s \"%s\"\n", YELLOW, RESET, line);
	head = init_list(line);
	if (!head)
	{
		printf("%s   -> List is empty or failed to initialize.%s\n",
			RED, RESET);
		return ;
	}
	print_token_list(head);
	free_tokens(&head);
	printf("\n");
}
