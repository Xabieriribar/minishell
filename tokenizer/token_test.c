/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:26:09 by rick              #+#    #+#             */
/*   Updated: 2026/01/21 15:37:38 by rick             ###   ########.fr       */
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

/*
int	main(void)
{
	printf("TEST 1: Standard Pipe and Redirection\n");
	test_init_list("< infile grep 'Hello World' | cat > outfile");
	printf("\n\nTEST 2: Sticky Operators (No spaces)\n");
	test_init_list("<infile grep|cat>outfile");
	printf("\n\nTEST 3: Double Quotes with Variables & Spaces\n");
	test_init_list("echo \"   Spaces   should   be   kept   $USER  \"");
	printf("\n\nTEST 4: Append and Heredoc\n");
	test_init_list("cat << LIMITER >> append_file.txt");
	printf("\n\nTEST 5: Mixed Quotes\n");
	test_init_list("grep \"Search Term\" 'file with spaces.txt'");
	printf("\n\nTEST 6: Consecutive Operators (Tokenizer Stress)\n");
	test_init_list("ls ||| cat >>> file");
	printf("\n\nTEST 7: Empty Quotes (Should be empty tokens)\n");
	test_init_list("echo \"\" ''");
	printf("\n\nTEST 8: Error - Unclosed Single Quote\n");
	test_init_list("echo 'This is unclosed");
	printf("\n\nTEST 9: Error - Unclosed Double Quote\n");
	test_init_list("echo \"This is unclosed");
	printf("\n\nTEST 10: Complex Mix\n");
	test_init_list("<in cat -e | grep \"pattern\"|wc -l >out");
	return (0);
}
*/