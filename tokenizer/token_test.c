/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:26:09 by rick              #+#    #+#             */
/*   Updated: 2026/02/18 10:11:01 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	*get_type_str(t_type type)
{
	if (type == T_CMD || type == T_WORD) return ("WORD");
	if (type == T_PIPE) return ("PIPE");
	if (type == T_REDIR_IN) return ("RED_IN");
	if (type == T_REDIR_OUT) return ("RED_OUT");
	if (type == T_REDIR_APPEND) return ("APPEND");
	if (type == T_HEREDOC) return ("HEREDOC");
	return ("UNKNOWN");
}*/

/* 
* Converts tokens into the debug format: "WORD(ls), PIPE, WORD(wc)" 
* This is what makes the Result match the Expected text file.*/
/*static char	*tokens_to_string(t_token *tokens)
{
	char	*result;
	char	*tmp;
	char	buffer[10000];

	result = ft_strdup("");
	while (tokens)
	{
		char *type_str = get_type_str(tokens->type);
		if (tokens->type == T_WORD || tokens->type == T_CMD)
		{
			sprintf(
				buffer,
				"%s(%s)",
				type_str,
				tokens->value ? tokens->value : ""
			);
		}
		else
			sprintf(buffer, "%s", type_str);

		tmp = result;
		result = ft_strjoin(result, buffer);
		free(tmp);
		if (tokens->next)
		{
			tmp = result;
			result = ft_strjoin(result, ", ");
			free(tmp);
		}
		tokens = tokens->next;
	}
	return (result);
}

int	tokenizer_test(char *file_path)
{
	int		fd;
	int		percentage = 0;
	int		n_tests = 0;
	char	*line;
	char	*command;
	char	*exp_output;
	char	*result;
	t_token	*tokens;

	setenv("USER", "john", 1);
	setenv("HOME", "/home/john", 1);
	setenv("VAR1", "4242", 1);

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (printf("%sError: Open file %s%s\n", RED, file_path, RESET), -1);
	printf("\n%s=== STARTING TOKENIZER TESTS ===%s\n", CYAN, RESET);
	while ((line = get_next_line(fd)))
	{
		line[strcspn(line, "\n")] = '\0';
		
		if (*line == '\0' || line[0] == '#')
		{
			if (line[0] == '#') 
				printf("\n%s%s%s\n", YELLOW, line, RESET);
			free(line);
			continue;
		}

		command = strtok(line, "::");
		exp_output = strtok(NULL, "::");

		if (!command || !exp_output)
		{
			free(line);
			continue;
		}
		tokens = init_list(command); 
		result = tokens_to_string(tokens);
		if (strcmp(result, exp_output) == 0)
		{
			printf("%s[PASS] %s%s\n", GREEN, command, RESET);
			percentage++;
		}
		else
		{
			printf("%s[FAIL] %s%s\n", RED, command, RESET);
			printf("      %sEXPECTED: %s%s\n", CYAN, exp_output, RESET);
			printf("      %sRESULT  : %s%s\n", RED, result, RESET);
		}
		n_tests++;
		free(result);
		free_tokens(&tokens);
		free(line);
	}
	close(fd);
	if (n_tests > 0)
		percentage = percentage * 100 / n_tests;
	else
		percentage = 0;
	printf(
		"\n%sRESULT:%s [%d%%] Passed\n",
		percentage == 100 ? GREEN : RED,
		RESET,
		percentage
	);
	return (0);
}*/
