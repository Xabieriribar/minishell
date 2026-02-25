#include "minishell.h"

int	g_signal = 0;

/*
* This function mallocs the data struct it and initializes its values to NULL
* It returns the struct on success and 1 when somethings goes wrong*/
t_data	*init_data(char **env_variables)
{
	t_data	*data;

	data = malloc(sizeof(struct s_data));
	if (!data)
		return (perror("Err: Malloc"), NULL);
	data->env_var = init_env_list(env_variables);
	data->exit_status = 0;
	data->pid_count = 0;
	data->recursive_call_counter = 0;
	data->fd_in = 0;
	data->fd_out = 0;
	data->pid_values = malloc(sizeof(int) * 1024);
	return (data);
}

/*
* Function to run in case of having an input during the main loop
- LOGIC:

* Create the tokens out of that input.
* Validate the tokens according to the expected shell grammar
* Init the AST
* Execute
* Free*/
/*static void	process_input(char *input, t_data *data)
{
	t_token	*token;
	t_token	*temp_token;
	t_node	*tree;

	add_history(input);
	token = init_list(input, data);
	if (!token)
		return ;
	temp_token = token;
	if (grammar_validator(token) != 0)
	{
		data->exit_status = 2;
		free_tokens(&temp_token);
		return ;
	}
	tree = init_tree(&token);
	data->ast_head = tree;
	data->token_head = temp_token;
	execute(tree, data);
	free_tokens(&temp_token);
	data->token_head = NULL;
	free_tree(tree);
	data->ast_head = NULL;
}*/
void	process_input(char *input, t_data *data)
{
	t_token	*token;
	t_token	*temp;
	t_node	*tree;

	token = init_list(input, data);
	if (!token)
		return ;
	temp = token;
	if (grammar_validator(token) != 0)
	{
		data->exit_status = 2;
		free_tokens(&temp);
		return ;
	}
	tree = init_tree(&token);
	data->ast_head = tree;
	data->token_head = temp;
	execute(tree, data);
	free_tokens(&temp);
	data->token_head = NULL;
	free_tree(tree);
	data->ast_head = NULL;
}

/*
* Main shell loop:
* Will ask the user for a prompt with readline()
* in case of no input it will exit
* Otherwise will call process_input()
* If we recieve the code -42 from b_exit() the loop is finished.*/
static void	shell_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			free_env_vars(&(data->env_var));
			rl_clear_history();
			exit(0);
		}
		if (input && *input)
		{
			process_input(input, data);
			if (data->exit_true == -42)
				break ;
		}
		free(input);
	}
	if (input)
		free(input);
}

/*
~ TO ERRASE !!!!!!!!!!!!*/
// static void	run_tester(char *input, t_data *data)
// {
// 	t_token	*token;
// 	t_token	*temp;
// 	t_node	*tree;

// 	token = init_list(input, data);
// 	if (!token)
// 		free_all_and_exit(data, 0);
// 	temp = token;
// 	if (grammar_validator(token) != 0)
// 	{
// 		data->exit_status = 2;
// 		free_tokens(&temp);
// 	}
// 	else
// 	{
// 		tree = init_tree(&token);
// 		data->ast_head = tree;
// 		data->token_head = temp;
// 		execute(tree, data);
// 		free_tokens(&temp);
// 		data->token_head = NULL;
// 		free_tree(tree);
// 		data->ast_head = NULL;
// 	}
// 	free_all_and_exit(data, data->exit_status);
// }
static void	run_c_flag(char *arg, t_data *data)
{
	char	**arg_input;
	int		i;

	arg_input = ft_split(arg, ';');
	if (!arg_input)
		free_all_and_exit(data, 1);
	i = 0;
	while (arg_input[i])
	{
		process_input(arg_input[i], data);
		i++;
	}
    // Don't forget to free the 2D array created by ft_split!
	free_splits(arg_input, -1); 
}

int	main(int ac, char **av, char **ep)
{
	t_data	*data;
	int		exit_code;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	data = init_data(ep);
 	if (ac == 3 && ft_strncmp(av[1], "-c", 3) == 0 && av[2])
			run_c_flag(av[2], data);
	else
		shell_loop(data);
	exit_code = data->exit_status;
	free_data(data);
	rl_clear_history();
	return (exit_code);
}