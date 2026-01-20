/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/01/20 14:45:17 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
