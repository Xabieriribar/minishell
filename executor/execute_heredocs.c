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
* Reads line by line from standard input using readline until the exact 
* delimiter is entered. The input is written to the provided file descriptor.
*/
int	execute_heredoc(int fd_heredoc, char *delimiter)
{
	char	*line;
	size_t	len;

	line = NULL;
	len = ft_strlen(delimiter) + 1;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (!ft_strncmp(line, delimiter, len))
		{
			free(line);
			break ;
		}
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	close(fd_heredoc);
	return (0);
}

/*
* Handles the creation of a single heredoc: generates a unique filename 
* in /tmp, opens it with secure 0644 permissions, and runs the input loop.
* The original filename in the redir node is replaced with the temp path.
*/
static void	process_single_heredoc(t_redirs *redir, int *index)
{
	int		fd;
	char	*num_str;

	num_str = ft_itoa(*index);
	redir->temp_heredoc_filename = ft_strjoin("/tmp/.heredoc_", num_str);
	free(num_str);
	fd = open(redir->temp_heredoc_filename,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell: heredoc: open failed");
	execute_heredoc(fd, redir->filename);
	redir->filename = redir->temp_heredoc_filename;
	*index += 1;
}

/*
* Iterates through the redirection list of a command node to find 
* and process any Heredoc tokens.
*/
void	search_and_execute_heredoc(t_redirs *redirs, int *index)
{
	t_redirs	*temp;

	temp = redirs;
	while (temp)
	{
		if (temp->redir_type == T_HEREDOC)
			process_single_heredoc(temp, index);
		temp = temp->next;
	}
}

/*
* Helper function to check if a redirection list contains any Heredocs.
*/
int	contains_heredoc_redirs(t_redirs *redirs)
{
	t_redirs	*ptr;

	ptr = redirs;
	while (ptr)
	{
		if (ptr->redir_type == T_HEREDOC)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

/*
* Recursively traverses the AST to open all Heredocs before execution begins.
* This ensures user interaction happens in the correct order for pipes.
*/
void	open_temporary_heredocs(t_node *tree, int *heredoc_file_index)
{
	if (!tree)
		return ;
	if (tree->node_type == COMMAND)
	{
		if (tree->redirs != NULL && contains_heredoc_redirs(tree->redirs))
			search_and_execute_heredoc(tree->redirs, heredoc_file_index);
		return ;
	}
	open_temporary_heredocs(tree->left_child, heredoc_file_index);
	open_temporary_heredocs(tree->right_child, heredoc_file_index);
}
