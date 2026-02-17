/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 11:56:33 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:28:36 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_token_lstsize(t_token *lst)
{
	int		i;
	t_token	*ptr;

	if (!lst)
		return (0);
	i = 1;
	ptr = lst;
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

int	ft_is_append_or_heredoc(t_type type)
{
	if (type == T_HEREDOC)
		return (1);
	else if (type == T_REDIR_APPEND)
		return (2);
	return (0);
}

int	ft_handle_error_message(t_type redir_type)
{
	if (redir_type == T_REDIR_APPEND)
		return (printf("parse error near '>>'\n"), 1);
	else if (redir_type == T_HEREDOC)
		return (printf("parse error near '<<'\n"), 1);
	else if (redir_type != T_HEREDOC && redir_type != T_REDIR_APPEND)
		return (printf("parse error near '|'\n"), 1);
	return (0);
}

int	ft_handle_redirs(t_token *head, int lst_len, int lst_index)
{
	if (ft_is_redir(head->type) == 0)
	{
		if (lst_len == lst_index)
			return (printf("parse error near 'newline'\n"), 1);
		else if (head->next->type != T_WORD)
		{
			if (ft_handle_error_message(head->next->type) != 0)
				return (1);
		}
		else if (ft_is_append_or_heredoc(head->type) != 0)
		{
			if (head->prev->type != T_WORD)
			{
				printf("syntax error near unexpected token '<<'\n");
				return (1);
			}
		}
	}
	return (0);
}
