/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:38:46 by rspinell          #+#    #+#             */
/*   Updated: 2026/02/23 13:39:11 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_and_exit(t_data *data, int exit_status)
{
	if (data)
	{
		if (data->token_head)
			free_tokens(&(data->token_head));
		if (data->ast_head)
			free_tree(data->ast_head);
		free_data(data);
	}
	exit(exit_status);
}
