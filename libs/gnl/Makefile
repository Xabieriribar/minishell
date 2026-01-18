SRCS = \
	get_next_line_utils.c \
	get_next_line.c \

OBJS := $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror

NAME = gnl.a

all: $(NAME)

# Build the static library
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
# Take all the .c files and pre-compile the .o files needed for creating the lib
%.o: %.c
	cc $(CFLAGS) -c $< -o $@

# Remove the object files
clean:
	rm -rf $(OBJS)

# Run clean and then remove the library as well
fclean: clean
	rm -rf $(NAME)

# Run fclean and then Re-build the library
re: fclean all

# Clarify with phony that this are commands and not files
.PHONY: clean fclean re all bonus
