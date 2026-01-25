/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/01/25 19:08:42 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	test_init_list("ls|echo", NULL);
	return (0);
}

/* int	main(void)
{
	char	*input;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			return (0);
		test_init_list(input, NULL);
		free(input);
	}
	return (0);
} */

/*
int	main(void)
{
	printf("\n%s= 1. Basic Commands & Spaces =%s\n", CYAN, RESET);
	test_init_list("ls", "WORD(ls)");
	test_init_list("ls -la", "WORD(ls), WORD(-la)");
	test_init_list("echo hello world", "WORD(echo), WORD(hello), WORD(world)");
	test_init_list("   ls -l   ", "WORD(ls), WORD(-l)");
	test_init_list("ls       -la", "WORD(ls), WORD(-la)");
	test_init_list("/bin/ls", "WORD(/bin/ls)");
	test_init_list("./minishell", "WORD(./minishell)");
	test_init_list("echo \"\"", "WORD(echo), WORD()");
	test_init_list("echo \" \"", "WORD(echo), WORD( )");
	test_init_list("\"\" \"\"", "WORD(), WORD()");

	printf("\n%s== 2. Single Quotes %s(Literal - D=FALSE)%s =%s\n", CYAN, RED, CYAN, RESET);
	test_init_list("'ls -la'", "WORD(ls -la)");
	test_init_list("echo '   hello   '", "WORD(echo), WORD(   hello   )");
	test_init_list("echo '$USER'", "WORD(echo), WORD($USER) [D=FALSE]");
	test_init_list("echo 'quote \"in\" quote'", "WORD(echo), WORD(quote \"in\" quote)");
	test_init_list("''", "WORD()");
	test_init_list("' '", "WORD( )");
	test_init_list("cat 'file name'", "WORD(cat), WORD(file name)");

	printf("\n%s== 3. Double Quotes %s(Expansion - D=TRUE)%s =%s\n", CYAN, GREEN, CYAN, RESET);
	test_init_list("\"ls -la\"", "WORD(ls -la)");
	test_init_list("echo \"hello $USER\"", "WORD(echo), WORD(hello $USER) [D=TRUE]");
	test_init_list("echo \"'single quotes'\"", "WORD(echo), WORD('single quotes')");
	test_init_list("\"       \"", "WORD(       )");
	test_init_list("echo \"pipe | in quotes\"", "WORD(echo), WORD(pipe | in quotes)");
	test_init_list("echo \"> redir in quotes\"", "WORD(echo), WORD(> redir in quotes)");
	test_init_list("echo \"$?\"", "WORD(echo), WORD($?) [D=TRUE]");

	printf("\n%s== 4. Token Concatenation (Glue) =%s\n", CYAN, RESET);
	test_init_list("echo\"hello\"", "WORD(echohello)");
	test_init_list("ls\"-la\"", "WORD(ls-la)");
	test_init_list("echo'hello'world", "WORD(echohelloworld)");
	test_init_list("cat\"file\"'name'", "WORD(catfilename)");
	test_init_list("\"\"ls", "WORD(ls)");
	test_init_list("ls\"\"", "WORD(ls)");

	printf("\n%s= 5. Simple Redirections & Pipes =%s\n", CYAN, RESET);
	test_init_list("ls|wc", "WORD(ls), PIPE, WORD(wc)");
	test_init_list("ls | wc", "WORD(ls), PIPE, WORD(wc)");
	test_init_list("cat<file", "WORD(cat), RED_IN, WORD(file)");
	test_init_list("ls>file", "WORD(ls), RED_OUT, WORD(file)");
	test_init_list("ls>>file", "WORD(ls), APPEND, WORD(file)");
	test_init_list("cat<<limit", "WORD(cat), HEREDOC, WORD(limit)");
	test_init_list("ls | wc | grep 0", "WORD(ls), PIPE, WORD(wc), PIPE, WORD(grep), WORD(0)");
	test_init_list("ls|wc|grep|awk", "WORD(ls), PIPE, WORD(wc), PIPE, WORD(grep), PIPE, WORD(awk)");

	printf("\n%s===== 6. Mixed Operators & Commands =%s\n", CYAN, RESET);
	test_init_list("ls -l | grep .c > out", "WORD(ls), WORD(-l), PIPE, WORD(grep), "
		"WORD(.c), RED_OUT, WORD(out)");
	test_init_list("cat < in | wc -l > out", "WORD(cat), RED_IN, WORD(in), PIPE, WORD(wc), "
		"WORD(-l), RED_OUT, WORD(out)");
	test_init_list("ls > out | wc -l", "WORD(ls), RED_OUT, WORD(out), PIPE, WORD(wc), WORD(-l)");
	test_init_list("> out ls", "RED_OUT, WORD(out), WORD(ls)");
	test_init_list("ls -l > out1 -a > out2", "WORD(ls), WORD(-l), RED_OUT, WORD(out1), "
		"WORD(-a), RED_OUT, WORD(out2)");
	test_init_list("cat < in | grep a >> out | wc -l", "WORD(cat), RED_IN, WORD(in), PIPE, "
		"WORD(grep), WORD(a), APPEND, WORD(out), PIPE, WORD(wc), WORD(-l)");

	printf("\n%s===== 7. The Evil Tests =====%s\n", CYAN, RESET);
	test_init_list("ls | | wc", "WORD(ls), PIPE, PIPE, WORD(wc)");
	test_init_list("ls > > out", "WORD(ls), RED_OUT, RED_OUT, WORD(out)");
	test_init_list("| ls", "PIPE, WORD(ls)");
	test_init_list("ls |", "WORD(ls), PIPE");
	test_init_list("ls >", "WORD(ls), RED_OUT");
	test_init_list("\"\" | '' > \" \"", "WORD(), PIPE, WORD(), RED_OUT, WORD( )");

	printf("\n%s===== 8. Dollar & Expansion Tests =====%s\n", CYAN, RESET);
	test_init_list("echo $USER", "WORD(echo), WORD($USER) [D=TRUE]");
	test_init_list("echo '$USER'", "WORD(echo), WORD($USER) [D=FALSE]");
	test_init_list("echo \"Hello $HOME\"", "WORD(echo), WORD(Hello $HOME) [D=TRUE]");
	test_init_list("echo \"\"$HOME\"\"", "WORD(echo), WORD($HOME) [D=TRUE]");

	printf("\n%s===== 9. Spaces & Empty Quotes =====%s\n", CYAN, RESET);
	test_init_list("echo \"\" '' \" \"", "WORD(echo), WORD(), WORD(), WORD( )");
	test_init_list("\"\"\"\"", "WORD(), WORD()");
	test_init_list("ls    \"file name\"   -l", "WORD(ls), WORD(file name), WORD(-l)");

	return (0);
}*/