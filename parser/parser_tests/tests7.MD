WORD PIPE WORD PIPE WORD (command: ls | grep a | wc)
Result:
typedef struct s_node {
    t_type node = CMD_PIPE
    t_node *left = a pipe node that has a left child called ls and a right child called grep a
    t_node *right = the wc command node
    t_node *child = NULL
    char **args = NULL
    t_redir redir = NULL
}