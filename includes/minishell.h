/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:38:42 by rick              #+#    #+#             */
/*   Updated: 2026/01/26 12:10:09 by rick             ###   ########.fr       */
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
	t_type		type;
	char		*value;
	int			index;
	int			dolar;
	t_token		*next;
	t_token		*prev;
};

typedef struct s_redirs
{
	t_type	redir_type;
	char	*filename;
	t_redirs	*next;
}	t_redirs;

typedef enum s_node_type
{
	COMMAND,
	PIPE,
} t_node_type;


typedef struct s_node t_node;
s_node
{
	t_node_type	node_type;
	char	**args;
	t_redirs	*redirs;
	t_node *right_child;
	t_node *left_child;
} t_node;

// ----------- TOKENIZER ---------- //

void	lst_add_back_token(t_token **lst, t_token *new);
t_token	*lstlast_token(t_token *lst);
void	free_tokens(t_token **head);
void	set_type(t_token *token, char *str);
void	set_dolar(t_token **head);

bool	is_single(char c);
bool	is_double(char c);
bool	is_space(char c);
bool	is_operator(char c);

t_token	*init_list(char *str);
int		init_add_token(t_token **head, char *str, int ix, int separated);

int		token_operator(t_token **head, char *str, int ix);
int		token_single(t_token **head, char *str, int ix);
int		token_double(t_token **head, char *str, int ix);
int		token_word(t_token **head, char *str, int ix);

int		token_single_append(t_token *last, char *str);
int		token_double_append(t_token *last, char *str);
int		token_word_append(t_token *last, char *str);

void	test_init_list(char *line, char *expected);

// ----------- SIGNALS ---------- //

void	sigint_handler(int sig);
int test_grammar(int fd_grammar_tester);
char *grammar_validator(t_token *head);
int		ft_token_lstsize(t_token *lst);
int		ft_is_redir(t_type type);
int		ft_is_append_or_heredoc(t_type type);
void	test_init_list(char *line, char *expected);
char	*ft_type_to_str(t_token *lst);
#endif

// ----------- PARSER ---------- //
int test_tree(int fd_tree_tester);
int init_tree(t_token *token_list);
