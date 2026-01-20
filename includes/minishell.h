/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:38:42 by rick              #+#    #+#             */
/*   Updated: 2026/01/18 13:00:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stdlib.h>

typedef enum e_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_type;

typedef struct s_token
{
	t_type	type;
	char	*value;
	int		index;
	struct s_token *next;
}	t_token;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	// NODE_AND;
	// NODE_OR;
	// NODE_SUBSHELL;
} t_node_type;

typedef struct s_redir
{
	t_type			redir_type;
	char			*filename;
	struct s_redir	*next;
} t_redir;

typedef struct s_node {
	t_node_type node_type;
	struct s_node *left_child;
	struct s_node *right_child;
	// t_node *child ONLY FOR BONUS
	t_redir *redir;
} t_node;

#endif