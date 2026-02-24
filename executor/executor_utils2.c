/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:34:47 by rspinell          #+#    #+#             */
/*   Updated: 2026/02/23 17:44:24 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Iterates through PATH directories to find the executable binary.
*/
char	*finds_directory(char *command, char *path, t_data *data)
{
	char	**dirs;
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	if (!ft_strncmp(command, "..", 3))
		command_not_found_error(command, data);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		res = ft_strjoin(tmp, command);
		free(tmp);
		if (res && access(res, F_OK) != -1)
			return (free_splits(dirs, i), res);
		free(res);
		i++;
	}
	free_splits(dirs, i);
	return (command_not_found_error(command, data), NULL);
}

/*
* Determines the full path of a command, handling absolute/relative paths.
*/
char	*get_path(char *command, char *path, t_data *data)
{
	char	*final_path;
	int		flag;

	flag = 0;
	if (!path || !command)
		return (NULL);
	if (!contains_slash(command))
	{
		final_path = finds_directory(command, path, data);
		flag = 1;
	}
	else
		final_path = command;
	check_possible_errors(final_path, data, flag);
	return (final_path);
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
* Handles specific error cases for pathnames and exits the child process.
*/
void		check_possible_errors(char *cmd, t_data *data, int flag)
{
	struct	stat st;

	if (stat(cmd, &st) == -1)
		no_such_file_or_directory_error(cmd, data, flag);
	if (S_ISDIR(st.st_mode))
		is_a_directory_error(cmd, data);
	if (access(cmd, X_OK) == -1)
		permission_denied_error(cmd, data, flag);

}

int is_parent_builtin(char *str)
{
	if (!str || !*str)
		return (0);
	if (!ft_strncmp(str, "exit", 5))
		return (1);
	if (!ft_strncmp(str, "cd", 3))
		return (1);
	if (!ft_strncmp(str, "unset", 6))
		return (1);
	if (!ft_strncmp(str, "export", 7))
		return (1);
	return (0);
}
