/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/21 10:18:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// int main(void)
// {
// 	int fd_grammar_tester = open("parser/grammar_tests/grammar_tester.txt", O_RDONLY);
// 	if (fd_grammar_tester < 0)
// 		perror("Failed to open tester file");
// 	if (test_grammar(fd_grammar_tester) != 0)
// 		return (perror("Failed to test grammar"), 1);
// 	return 0;
// }
volatile sig_atomic_t g_status = 0;
/*This function mallocs the data struct it and initializes its values to NULL
It returns the struct on success and 1 when somethings goes wrong*/
t_data *init_data(char **env_variables)
{
    t_data *data;

    data = malloc(sizeof(struct s_data));
    if (!data)
        return (perror("Malloc failed when initializing the data struct"), NULL);
    data->env_var = init_env_list(env_variables);
    data->exit_status = 0;
    data->pid_count  = 0;
    data->recursive_call_counter = 0;
    /* WE ALLOCATE 1024 FOR A GENEROUS AMOUNT OF PIPE. PAY ATTENTION, THIS CAN BREAK STRESS TESTS AND MUST BE TREATED*/
    data->pid_values = malloc(sizeof(int) * 1024);
    return (data);

}
/*This functino takes the data structure as an argument and frees the elements that were allocated to it*/
void    free_data(t_data *data)
{
	free_env_vars(&(data->env_var));
    free(data->pid_values);
    free(data);
}
// int	main(int ac, char **av, char **ep)
// {
// 	(void)ac;
// 	(void)av;
//     t_data  *data;
//     t_node  *tree;
// 	char    *input;
// 	t_token *token;
//     t_token *temp_token;

//     data = init_data();
//     if (!data)
// 		return (1);
// 	data->env_var = init_env_list(ep);
// 	signal(SIGINT, sigint_handler);
//     signal(SIGQUIT, SIG_IGN);
//     while (1)
//     {
//         input = readline(PROMPT);
//         if (!input)
//         {
//             printf("exit\n");
// 			free_env_vars(&data->env_var);
// 			rl_clear_history();
//             exit(0);
//         }
//         if (input && *input)
//         {
//             add_history(input);
//             token = init_list(input);
//             temp_token = token;
//             tree = init_tree(&token);
//             execute_pipeline(tree, 0, 1, data);
//             /* Why do we initialise the pid_count to 0? The command execution has ended, but the pid_count value has been changed. Therefore,
//             we need to set its value to 0 to not break the next command*/
//             data->pid_count = 0;
//             printf("%d", data->exit_status);
//             free_tree(tree);
// 			free_tokens(&temp_token);
//         }
//         free(input);
//     }
// 	free_env_vars(&data->env_var);
// 	rl_clear_history();
//     return (0);
// }
int	main(int ac, char **av, char **ep)
{
	t_data	*data;
	char	*input;
	t_token	*token;
    t_node  *tree;
    t_token *temp_token;

	(void)ac;
	(void)av;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
    data = init_data(ep);
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			printf("exit\n");
			free_env_vars(&(data->env_var));
			rl_clear_history();
			exit(0);
		}
		if (input && *input)
		{
			add_history(input);
			token = init_list(input);
            temp_token = token;
			if (grammar_validator(token) != 0)
			{
				data->exit_status = 2;
				free_tokens(&temp_token);
				free(input);
				continue ;
			}
            tree = init_tree(&token);
            execute(tree, data);
			free_tokens(&temp_token);
            free_tree(tree);
			if (data->exit_status == -42)
				break ;
		}
		free(input);
	}
	if (input)
		free(input);
	rl_clear_history();
	int asd = data->exit_status;
    free_data(data);
	return (asd);
}
