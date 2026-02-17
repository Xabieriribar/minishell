/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:28:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	free_args(char **args)
{
	if (!args)
		return ;
	free(args);
}

void	free_redirs(t_redirs *redirs)
{
	t_redirs	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}

void	free_tree(t_node *node)
{
	if (!node)
		return ;
	free_tree(node->left_child);
	free_tree(node->right_child);
	if (node->args)
		free(node->args);
	if (node->redirs)
		free_redirs(node->redirs);
	free(node);
}
