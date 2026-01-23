/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:38:42 by rick              #+#    #+#             */
/*   Updated: 2026/01/23 16:13:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET   "\033[0m"
# define GREEN   "\033[32m"
# define CYAN    "\033[36m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define RED     "\033[31m"

# define PROMPT "\033[45m\002>>> \033[33m\002Minishell>$ \033[0m\002"

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h> 
# include <signal.h>

typedef enum e_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
}	t_type;

typedef struct s_token	t_token;

struct s_token
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

void	lst_add_back_token(t_token **lst, t_token *new);
t_token	*lstlast_token(t_token *lst);
void	free_tokens(t_token **head);
void	set_types(t_token **head);
void	set_dolar(t_token **head);

bool	is_single(char c);
bool	is_double(char c);
bool	is_space(char c);
bool	is_operator(char c);

t_token	*init_list(char *str);
int		init_add_token(t_token **head, char *str, int ix);
int		token_operator(t_token **head, char *str, int ix);
int		token_single(t_token **head, char *str, int ix);
int		token_double(t_token **head, char *str, int ix);
int		token_word(t_token **head, char *str, int ix);

void	test_init_list(char *line, char *expected);

// ----------- SIGNALS ---------- //

void	sigint_handler(int sig);

#endif
