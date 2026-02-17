CC       = cc
CFLAGS   = -Wall -Wextra -Werror -g -I/usr/local/opt/readline/include
LDFLAGS  = -L/usr/local/opt/readline/lib -lreadline
INCLUDES = ./includes ./libs/libft ./libs/gnl

# ---------------- LIBRARY ----------------
LIBFT_DIR = libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = libs/gnl
GNL = $(GNL_DIR)/gnl.a

# ---------------- SOURCE ----------------
SRCS = \
	main.c \
	tokenizer/token_init.c \
	tokenizer/token_test.c \
	tokenizer/token_utils.c \
	tokenizer/token_bool.c \
	tokenizer/token_handler.c \
	tokenizer/token_append.c \
	expander/expander.c \
	expander/expander_utils.c \
	expander/test_exp.c \
	signals/signals.c \
	parser/grammar_tester.c \
	parser/grammar_validator.c \
	parser/parser_utils.c \
	built_in/cd.c \
	built_in/pwd.c \
	parser/create_tree_utils.c \
	parser/create_tree.c \
	parser/test_trees.c \
	parser/free_tree.c \
	executor/executor.c \
	executor/executor_utils.c \
	executor/execute_heredocs.c \
	executor/execute_redirs.c \
	executor/parse_env_vars.c \
	built_in/echo.c \
	built_in/builtins.c \
	built_in/builtins_utils.c \
	built_in/env.c \
	built_in/unset.c \
	built_in/exit.c \
	built_in/export.c \
	parser/grammar_tester.c \
	parser/grammar_validator.c \
	parser/parser_utils.c \

# ------------- COMPILING ----------------

OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(LIBFT) $(GNL) $(NAME) 

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL):
	$(MAKE) -C $(GNL_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(GNL) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(addprefix -I, $(INCLUDES)) $(LFLAGS) -c $< -o $@

# ------------ CLEAN RULES --------------

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GNL_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GNL_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
