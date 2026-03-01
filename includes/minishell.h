/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:38:42 by rick              #+#    #+#             */
/*   Updated: 2026/02/26 17:08:50 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* -------------------------------- MACROS ---------------------------------- */

# define RESET		"\033[0m"
# define GREEN		"\033[32m"
# define CYAN		"\033[36m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define RED		"\033[31m"

# define PROMPT			"Minishell>> "
# define PIPE_ERR_MSG	"syntax error near unexpected token `|'\n"
# define HDOC_ERR_MSG	"syntax error near unexpected token `>>'\n"
# define REDIR_ERR_MSG	"syntax error near unexpected token `newline'\n"

/* ------------------------------- INCLUDES --------------------------------- */

# include "libft.h"
# include "get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <sys/stat.h>

/* ------------------------------- GLOBALS ---------------------------------- */

extern int						g_signal;

/* ------------------------- STRUCTS & TYPEDEFS ----------------------------- */

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
	t_type	type;
	char	*value;
	int		index;
	int		dolar;
	bool	hdoc_expand;
	int		was_expanded;
	int		is_ghost;
	t_token	*next;
	t_token	*prev;
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirs
{
	t_type			redir_type;
	char			*filename;
	char			*temp_heredoc_filename;
	int				was_expanded;
	struct s_redirs	*next;
}	t_redirs;

typedef enum s_node_type
{
	COMMAND,
	PIPE,
}	t_node_type;

typedef struct s_node
{
	t_node_type		node_type;
	char			**args;
	struct s_redirs	*redirs;
	struct s_node	*right_child;
	struct s_node	*left_child;
}	t_node;

typedef struct s_data
{
	long	max_fd;
	long	i;
	int		exit_status;
	int		heredoc_file_index;
	int		flag;
	int		pid_count;
	int		*pid_values;
	int		recursive_call_counter;
	int		fd_in;
	int		fd_out;
	int		exit_true;
	t_env	*env_var;
	t_node	*ast_head;
	t_token	*token_head;
}	t_data;

/* ========================================================================== */
/* 								FUNCTIONS                                     */
/* ========================================================================== */

/* ------------------------------- TOKENIZER -------------------------------- */

void		lst_add_back_token(t_token **lst, t_token *new);
t_token		*lstlast_token(t_token *lst);
void		set_type(t_token *token, char *str);
void		set_dolar(t_token *token);
void		set_init(t_token *token, char *str, int ix, int flag);

bool		is_single(char c);
bool		is_double(char c);
bool		is_space(char c);
bool		is_operator(char c);
bool		is_dollar(char c);

t_token		*init_list(char *str, t_data *data);
int			init_add_token(t_token **head, char *str, int sep, t_data *data);

int			token_operator(t_token **head, char *str, int ix);
int			token_single(t_token **head, char *str, int ix);
int			token_double(t_token **head, char *str, int ix, t_data *data);
int			token_word(t_token **head, char *s, int ix, t_data *data);

int			token_single_append(t_token *last, char *str);
int			token_double_append(t_token *last, char *str, t_data *data);
int			token_word_append(t_token *last, char *str, t_data *data);

int			tokenizer_test(char *file_path);

/* ------------------------------- EXPANDER --------------------------------- */

char		*expander(t_token *token, t_data *data);
char		*expand_buff(char *str, t_data *data, t_token *token);
char		*ft_strconcat(char *s1, char *s2);
int			expander_test(char *address);
bool		valid_chars(char c);
char		*get_env_value(t_env *env, char *key);
char		*append_char(char *str, char c);

/* ------------------------------- BUILTINS --------------------------------- */

int			run_bultins(char **args, t_env **lst, t_data **data, int out_nmb);
t_env		*init_env_list(char **envp);
t_env		*init_env(char *str);
t_env		*lstlast_env(t_env *lst);
t_env		*find_env(t_env **env, char *key);
int			lst_add_back_env(t_env **lst, t_env *new);
void		print_env_list(t_env **head, int out_nmb);
int			env_list_size(t_env *env);
void		print_arr(t_env **arr, int size, int out_nmb);
void		sort_env_arr(t_env **arr, int size);
char		*get_key(char *str);

int			b_pwd(int out_nbr);
int			b_cd(t_env *env, char **args);
int			b_echo(char **args, int out_nmb);
int			b_env(char **arr, t_env **list, int out_nmb);
int			b_unset(t_env **env, char **arr);
int			b_exit(char **args, t_data **data);
int			b_export(char **arr, t_env **env, int out_nmb);

/* -------------------------------- PARSER ---------------------------------- */

int			test_grammar(int fd_grammar_tester);
int			grammar_validator(t_token *head);
int			ft_token_lstsize(t_token *lst);
int			ft_is_redir(t_type type);
int			ft_is_append_or_heredoc(t_type type);
int			ft_handle_redirs(t_token *head, int lst_len, int lst_index);

int			test_tree(int fd_tree_tester);
t_node		*init_tree(t_token **token_list);
void		run_tree_test(char *input_line);

void		fill_command_node(t_node *node);
int			ft_tokens_before_pipe(t_token *token_list);
int			move_pointer_to_next_pipe(t_token **token_list);
int			ft_next_token_is_pipe(t_token **token_list);
int			move_pointer_after_pipe(t_token **token_list);

int			find_number_of_redirs(t_token *token_list);
char		*find_enum_type(t_redirs *redirs);
void		ft_lstadd_back_redirs(t_redirs **lst, t_redirs *new);
t_redirs	*ft_lstlast_redirs(t_redirs *lst);
t_redirs	*ft_lstnew_redirs(char *filename, t_type redir_type);

/* ------------------------------- EXECUTION -------------------------------- */

void		execute(t_node *tree, t_data *data);
void		execute_pipeline(t_node *t, int fd_in, int fd_out, t_data *data);
void		open_temporary_heredocs(t_node *tree, int *heredoc_file_index);
void		unlink_heredoc_files(t_node *tree);

char		**convert_env_var_to_array(t_env *env_var, int env_var_lstsize);
int			ft_env_var_lstsize(t_env *env_var);
t_env		*return_path(t_env *env_var);
int			contains_slash(char *suspect);

int			update_fd(t_redirs *r, int *fd_in, int *fd_out, t_data *data);
void		close_if_not_stdin_or_stdout(int fd_in, int fd_out);
int			contains_out_redirs(t_redirs *redirs);
int			contains_in_redirs(t_redirs *redirs);

void		write_error_message(char *cmd);

char		*get_path(char *command, char *path, t_data *data);
void		wait_for_last_child(t_data *data);
int			is_parent_builtin(char *str);

/* -------------------------------- SIGNALS --------------------------------- */

void		sigint_handler(int sig);
void		set_signals_interactive(void);
void		set_signals_noninteractive(void);
void		set_signals_child(void);

/* ---------------------------- FREE FUNCTIONS ------------------------------ */

void		free_splits(char **strs, int index_allocated);
void		free_all_and_exit(t_data *data, int exit_status);
void		free_data(t_data *data);
void		free_tree(t_node *tree);
void		free_env_vars(t_env **head);
void		free_tokens(t_token **head);
void		free_loop(t_node *tree, t_token **token_list, char *input);

/* ---------------------------- UTILS / LIBFT ------------------------------- */

char		*ft_strdup(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_itoa(int n);
void		ft_putnbr_fd(int n, int fd);
void		ft_putchar_fd(char c, int fd);

/* ------------------------ ERRORS ------------------------------------- */

void		command_not_found_error(char *cmd, t_data *data);
void		no_such_file_or_directory_error(char *cmd, t_data *data, int flag);
void		is_a_directory_error(char *cmd, t_data *data);
void		permission_denied_error(char *cmd, t_data *data, int flag);
void		check_possible_errors(char *cmd, t_data *data, int flag);

#endif
