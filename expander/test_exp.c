/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:35:34 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 11:11:31 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *join_tokens(t_token *token)
{
	char *result;
	char *tmp;

	result = ft_strdup("");
	while (token)
	{
		tmp = result;
		result = ft_strjoin(result, token->value);
		free(tmp);
		if (token->next)
		{
			tmp = result;
			result = ft_strjoin(result, " ");
			free(tmp);
		}
		token = token->next;
	}
	return (result);
}

int expander_test(char *address)
{
	int		fd;
	int		percentage;
	int		n_tests;
	char	*line;
	char	*command;
	char	*exp_output;
	char	*result;
	t_token	*tokens;

	setenv("USER", "john", 1);
	setenv("HOME", "/home/john", 1);
	setenv("VAR1", "42", 1);

	percentage = 0;
	n_tests = 0;
	fd = open(address, O_RDONLY);
	if (fd < 0)
		return (printf("%sWrong address%s\n", RED, RESET), -1);
    printf("\n%s=== STARTING EXPANDER TESTS ===%s\n\n", CYAN, RESET);
	while ((line = get_next_line(fd)))
	{
		line[strcspn(line, "\n")] = '\0';
		if (*line == '\0' || line[0] == '#')
		{
			printf("%s%s%s\n", RED, line, RESET);
			free(line);
			continue;
		}
		command = strtok(line, "::");
		exp_output = strtok(NULL, "::");
		if (!command || !exp_output)
		{
			printf("%s[FORMAT ERROR]%s %s\n\n", RED, RESET, line);
			free(line);
			continue;
		}
		tokens = init_list(command);
		result = join_tokens(tokens);
		if (strcmp(result, exp_output) == 0)
		{
			printf("%s[PASS]%s\n", GREEN, RESET);
			percentage++;
			n_tests++;
		}
		else
		{
			printf("%s[FAIL]%s\n", RED, RESET);
			n_tests++;
		}
		printf("%sCOMMAND :%s %s\n", CYAN, RESET, command);
		printf("%sEXPECTED:%s %s\n", YELLOW, RESET, exp_output);
		printf("%sRESULT  :%s %s\n", BLUE, RESET, result);
		printf("\n");
		free(result);
		free_tokens(&tokens);
		free(line);
	}
	close(fd);
	percentage = percentage * 100 / n_tests;
	printf("\n%sPASSED TESTS:%s  [%i%%]%s\n", YELLOW, GREEN, percentage, RESET);
	return (0);
}
