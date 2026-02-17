/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:28:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_command_node(t_node *node)
{
	node->node_type = COMMAND;
	node->redirs = NULL;
	node->left_child = NULL;
	node->right_child = NULL;
}

int	ft_tokens_before_pipe(t_token *token_list)
{
	int	tokens_before_pipe;

	tokens_before_pipe = 0;
	while (token_list)
	{
		if (token_list->type != T_PIPE)
			tokens_before_pipe++;
		else
			return (tokens_before_pipe);
		token_list = token_list->next;
	}
	return (tokens_before_pipe);
}

int	move_pointer_to_next_pipe(t_token **token_list)
{
	while (*token_list)
	{
		if ((*token_list)->type == T_PIPE)
			return (1);
		*token_list = (*token_list)->next;
	}
	return (0);
}

int	ft_next_token_is_pipe(t_token **token_list)
{
	if (!*token_list)
		return (0);
	if ((*token_list)->type == T_PIPE)
		return (1);
	return (0);
}

int	move_pointer_after_pipe(t_token **token_list)
{
	if (*token_list)
		*token_list = (*token_list)->next;
	return (0);
}
