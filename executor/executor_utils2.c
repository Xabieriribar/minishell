/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:34:47 by rspinell          #+#    #+#             */
/*   Updated: 2026/02/23 14:02:42 by rspinell         ###   ########.fr       */
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
void	check_path_errors(char *pathname, char *cmd, t_data *data)
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
