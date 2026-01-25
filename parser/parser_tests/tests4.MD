WORD PIPE WORD WORD (command: ls | grep a)
Result:
typedef struct s_node {
    t_type node = CMD_PIPE
    t_node *left = address of the ls command node
    t_node *right = address of the grep a command node
    t_node *child = NULL
    char **args = NULL
    t_redir redir = NULL
}
