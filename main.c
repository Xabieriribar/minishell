/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/17 13:17:13 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_status = 0;

/* int main(void)
{
	char *str[] = {"cd", "../Common-Core", NULL};
 	char *str2[] = {"pwd", NULL};
	b_pwd(str2);
	b_cd(str);
	return (0);
} */

/* int	main(void)
{
	int fd_grammar_tester = open("parser/grammar_tests/grammar_tester.txt", O_RDONLY);
	if (fd_grammar_tester < 0)
		perror("Failed to open tester file");
	if (test_grammar(fd_grammar_tester) != 0)
		return (perror("Failed to test grammar"), 1);
	return 0;
}
	g_status = 42;
	tokenizer_test("./tokenizer/tokenizer_tests.txt");
	printf("\n\n");
	expander_test("./expander/expander_test.txt");
	return (0);
} */

char **get_args(t_token *token)
{
	char	**args;
	t_token	*ptr;
	int		len;
	int		i;

	ptr = token;
	len = 0;
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	ptr = token;
	i = 0;
	while (ptr)
	{
		args[i] = ptr->value;
		ptr = ptr->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	main(int ac, char **av, char **ep)
{
	(void)ac;
	(void)av;
	t_env *env_list;
	char *input;
	t_token *token;
	char **arr;

	env_list = init_env_list(ep);
	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        input = readline(PROMPT);
        if (!input)
        {
            printf("exit\n");
			free_env_vars(&env_list);
			rl_clear_history();
            exit(0);
        }
        if (input && *input)
        {
            add_history(input);
            token = init_list(input);
            arr = get_args(token);
            run_bultins(arr, &env_list);
			free_tokens(&token);
			if (arr)
					free(arr);
        }
        free(input);
    }
	free_env_vars(&env_list);
	rl_clear_history();
    return (0);
}