/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:38:42 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:27:48 by rick             ###   ########.fr       */
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
# include <sys/wait.h>


#ifndef MAX_FORK 1024
#define MAX_FORK 1024

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

typedef struct s_redirs
{
	t_type	redir_type;
	char	*filename;
	char	*temp_heredoc_filename;
	struct s_redirs *next;
}	t_redirs;

typedef enum s_node_type
{
	COMMAND,
	PIPE,
} t_node_type;

typedef struct s_node 
{
	enum s_node_type node_type;
	char	**args;
	struct s_redirs *redirs;
	struct s_node *right_child;
	struct s_node *left_child;
} t_node;
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
int		test_grammar(int fd_grammar_tester);
char	*grammar_validator(t_token *head);
int		ft_token_lstsize(t_token *lst);
int		ft_is_redir(t_type type);
int		ft_is_append_or_heredoc(t_type type);
char	*ft_type_to_str(t_token *lst);

#endif

// ----------- PARSER ---------- //
int test_tree(int fd_tree_tester);
t_node *init_tree(t_token **token_list);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int find_number_of_redirs(t_token *token_list);
char *find_enum_type(t_redirs *redirs);
void	ft_lstadd_back_redirs(t_redirs **lst, t_redirs *new);
t_redirs *ft_lstlast_redirs(t_redirs *lst);
t_redirs *ft_lstnew_redirs(char *filename, t_type redir_type);
void run_tree_test(char *input_line);
/* parser/create_tree_utils.c */
void	fill_command_node(t_node *node);
int		ft_tokens_before_pipe(t_token *token_list);
int		move_pointer_to_next_pipe(t_token **token_list);
int		ft_next_token_is_pipe(t_token **token_list);
int		move_pointer_after_pipe(t_token **token_list);
void    free_tree(t_node *tree);

/*EXECUTION*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int execute_pipeline(t_node *tree, int fd_in, int fd_out, int *pid_count, int *pid_values);