/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_validator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:28:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_simple_commands(t_token *head)
{
	int	no_word_len;

	no_word_len = 0;
	while (head)
	{
		if (head->type != T_WORD)
			no_word_len++;
		head = head->next;
	}
	if (no_word_len != 0)
		return (1);
	return (0);
}

int	ft_check_pipes(t_token *head)
{
	int	lst_len;
	int	lst_index;

	lst_len = ft_token_lstsize(head);
	lst_index = 1;
	if (head->type == T_PIPE)
		return (printf("parse error near '|'\n"), 1);
	while (head)
	{
		if (head->type == T_PIPE)
		{
			if (lst_len == lst_index)
				return (printf("parse error near '|'\n"), 1);
			else if (head->next && head->next->type == T_PIPE)
				return (printf("parse error near '|'\n"), 1);
			else if (head->prev && head->prev->type == T_REDIR_IN)
				return (printf("parse error near '|'\n"), 1);
		}
		lst_index++;
		head = head->next;
	}
	return (0);
}

int	ft_check_redirs(t_token *head)
{
	int	lst_len;
	int	lst_index;

	lst_index = 1;
	lst_len = ft_token_lstsize(head);
	while (head)
	{
		if (ft_handle_redirs(head, lst_len, lst_index) != 0)
			return (1);
		lst_index++;
		head = head->next;
	}
	return (0);
}

int	grammar_validator(t_token *head)
{
	if (ft_check_simple_commands(head) == 0)
		return (0);
	else if (ft_check_pipes(head) != 0)
		return (1);
	else if (ft_check_redirs(head) != 0)
		return (1);
	return (0);
}
