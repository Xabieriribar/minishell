/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/20 15:01:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Iterates through PATH directories to find the executable binary.
*/
char	*finds_directory(char *command, char *path)
{
	char	**dirs;
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		res = ft_strjoin(tmp, command);
		free(tmp);
		if (res && access(res, F_OK | X_OK) != -1)
			return (free_splits(dirs, -1), res);
		free(res);
		i++;
	}
	return (free_splits(dirs, -1), NULL);
}

/*
* Determines the full path of a command, handling absolute/relative paths.
*/
char	*get_path(char *command, char *path)
{
	if (!path || !command)
		return (NULL);
	if (contains_slash(command))
		return (can_access(command));
	return (finds_directory(command, path));
}

/*
* Handles specific error cases for pathnames and exits the child process.
*/
static void	check_path_errors(char *pathname, char *cmd, t_data *data)
{
	struct stat	st;

	if (!pathname)
	{
		write_error_message(cmd);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_all_and_exit(data, 127);
	}
	if (stat(pathname, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) || ft_strncmp(cmd, "./", 3) == 0)
		{
			write_error_message(cmd);
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
			free_all_and_exit(data, 126);
		}
		if (access(pathname, X_OK) == -1)
		{
			write_error_message(cmd);
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
			free_all_and_exit(data, 126);
		}
	}
}

/*
* Main execution logic for a single command node.
*/
void	execute_command(t_node *tree, t_data *data, int fd_in, int fd_out)
{
	t_env	*path_env;
	char	**env_arr;
	char	*path;

	close_if_not_stdin_or_stdout(fd_in, fd_out);
	path_env = return_path(data->env_var);
	if (!path_env)
		perror("minishell: PATH not set");
	path = get_path(tree->args[0], path_env->value);
	check_path_errors(path, tree->args[0], data);
	env_arr = convert_env_var_to_array(data->env_var,
			ft_env_var_lstsize(data->env_var));
	if (execve(path, tree->args, env_arr) == -1)
	{
		perror("minishell: execve");
		free(path);
		free_splits(env_arr, -1);
		free_all_and_exit(data, 127);
	}
}

/*
* Waits for all child processes in a pipeline and updates the exit status.
*/
void	wait_for_last_child(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pid_count)
	{
		waitpid(data->pid_values[i], &(data->exit_status), 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		else if (WIFSIGNALED(data->exit_status))
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		i++;
	}
}

/*
* Logic for a child process within the pipeline.
*/
static void	child_process(t_node *tree, int fd_in, int fd_out, t_data *data)
{
	int	i;

	if (tree->redirs != NULL)
	{
		data->flag = 0;
		update_fd(tree->redirs, &fd_in, &fd_out, data);
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	i = 3;
	while (i < 1024)
		close(i++);
	if (!tree->args || !tree->args[0])
		free_all_and_exit(data, EXIT_SUCCESS);
	if (run_bultins(tree->args, &(data->env_var), &data, fd_out) != -1)
		free_all_and_exit(data, data->exit_status);
	execute_command(tree, data, fd_in, fd_out);
}

/*
* Recursively executes the pipeline of commands.
*/
void	execute_pipeline(t_node *tree, int fd_in, int fd_out, t_data *data)
{
	pid_t	pid;
	int		pfd[2];

	if (tree->node_type == COMMAND)
	{
		pid = fork();
		if (pid == 0)
			child_process(tree, fd_in, fd_out, data);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
		data->pid_values[data->pid_count++] = pid;
	}
	else
	{
		if (pipe(pfd) < 0)
			perror("minishell: pipe failed");
		execute_pipeline(tree->left_child, fd_in, pfd[1], data);
		execute_pipeline(tree->right_child, pfd[0], fd_out, data);
		close(pfd[1]);
		close(pfd[0]);
	}
}

/*
* Executes a single command builtin in the parent process.
*/
void	execute_parent_builtin(t_node *tree, t_data *data)
{
	data->fd_in = STDIN_FILENO;
	data->fd_out = STDOUT_FILENO;
	if (tree->redirs != NULL)
	{
		data->flag = 1;
		if (update_fd(tree->redirs, &(data->fd_in),
				&(data->fd_out), data) == -1)
		{
			data->exit_status = 1;
			return ;
		}
	}
	run_bultins(tree->args, &(data->env_var), &data, data->fd_out);
	close_if_not_stdin_or_stdout(data->fd_in, data->fd_out);
}

/*
* Root execution function. Handles heredocs, parent builtins, and pipelines.
*/
void	execute(t_node *tree, t_data *data)
{
	data->heredoc_file_index = 0;
	open_temporary_heredocs(tree, &(data->heredoc_file_index));
	if (!tree->left_child && is_parent_builtin(tree->args[0]))
		execute_parent_builtin(tree, data);
	else
	{
		execute_pipeline(tree, STDIN_FILENO, STDOUT_FILENO, data);
		wait_for_last_child(data);
	}
}
