/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/23 17:18:11 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_type node_type)
{
	t_node	*node;

	if (node_type == T_PIPE)
	{
		node = malloc(sizeof(struct s_node));
		if (!node)
			return (NULL);
		node->node_type = PIPE;
		node->args = NULL;
		node->redirs = NULL;
		node->left_child = NULL;
		node->right_child = NULL;
		return (node);
	}
	return (NULL);
}

void	create_redirs_list(t_node *node, t_token *pointer_to_redir_token)
{
	t_redirs	*new_node;

	if (!node->redirs)
		node->redirs = ft_lstnew_redirs(pointer_to_redir_token->next->value,
				pointer_to_redir_token->type);
	else
	{
		new_node = ft_lstnew_redirs(pointer_to_redir_token->next->value,
				pointer_to_redir_token->type);
		ft_lstadd_back_redirs(&(node->redirs), new_node);
	}
}

int	create_multiple_args(t_node *node, t_token *token_list)
{
	int	index;

	index = 0;
	if (!node || !token_list)
		return (1);
	while (token_list && token_list->type != T_PIPE)
	{
		if (ft_is_redir(token_list->type) == 0)
		{
			create_redirs_list(node, token_list);
			token_list = token_list->next->next;
			continue ;
		}
		if (token_list->value)
		{
			node->args[index] = token_list->value;
			token_list = token_list->next;
			index++;
		}
		else
			token_list = token_list->next;
	}
	node->args[index] = NULL;
	return (0);
}

t_node	*parse_commands(t_token **token_list)
{
	t_node	*command_node;
	int		tokens_before_pipe;

	tokens_before_pipe = ft_tokens_before_pipe(*token_list);
	command_node = malloc(sizeof(struct s_node));
	if (!command_node)
		return (NULL);
	command_node->args = ft_calloc(tokens_before_pipe + 1, sizeof(char *));
	if (!command_node->args)
		return (free(command_node), NULL);
	fill_command_node(command_node);
	if (tokens_before_pipe == 1)
		command_node->args[0] = (*token_list)->value;
	else
	{
		if (create_multiple_args(command_node, *token_list) != 0)
			return (NULL);
	}
	move_pointer_to_next_pipe(token_list);
	return (command_node);
}

t_node	*init_tree(t_token **token_list)
{
	t_node	*current_root;
	t_node	*pipe_node;

	current_root = parse_commands(token_list);
	while (ft_next_token_is_pipe(token_list))
	{
		move_pointer_after_pipe(token_list);
		pipe_node = create_node(T_PIPE);
		if (!pipe_node)
			return (NULL);
		pipe_node->left_child = current_root;
		pipe_node->right_child = parse_commands(token_list);
		current_root = pipe_node;
	}
	return (current_root);
}
