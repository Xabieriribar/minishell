/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:38:42 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 18:27:43 by rick             ###   ########.fr       */
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
# include <fcntl.h>

extern volatile sig_atomic_t	g_status;

typedef enum e_type
{
	T_CMD,
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC,
}	t_type;

typedef struct s_token			t_token;

struct s_token
{
	t_type		type;
	char		*value;
	int			index;
	int			dolar;
	bool		hdoc_expand;
	t_token		*next;
	t_token		*prev;
};

typedef struct s_data
{
	int		exit_status;
}	t_data;

// ----------- TOKENIZER ---------- //

void	lst_add_back_token(t_token **lst, t_token *new);
t_token	*lstlast_token(t_token *lst);
void	free_tokens(t_token **head);
void	set_type(t_token *token, char *str);
void	set_dolar(t_token *token);
void	set_init(t_token *token, char *str, int ix, int flag);

bool	is_single(char c);
bool	is_double(char c);
bool	is_space(char c);
bool	is_operator(char c);
bool	is_dollar(char c);

t_token	*init_list(char *str);
int		init_add_token(t_token **head, char *str, int ix, int separated);

int		token_operator(t_token **head, char *str, int ix);
int		token_single(t_token **head, char *str, int ix);
int		token_double(t_token **head, char *str, int ix);
int		token_word(t_token **head, char *str, int ix);

int		token_single_append(t_token *last, char *str);
int		token_double_append(t_token *last, char *str);
int		token_word_append(t_token *last, char *str);

int		tokenizer_test(char *file_path);

// ----------- EXPANDER ---------- //

char	*expander(t_token *token);
char	*ft_strconcat(char *s1, char *s2);
int		expander_test(char *address);
bool	valid_chars(char c);

// ----------- BUILTINS ---------- //

int		b_pwd(char **args);
int 	b_cd(char **args);

// ----------- SIGNALS ---------- //

void	sigint_handler(int sig);

#endif
