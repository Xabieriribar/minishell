WORD WORD (command ls -la)
Result:
typedef struct s_node {
    t_type node = CMD_NODE
    t_node *left = NULL
    t_node *right = NULL
    t_node *child = NULL
    char **args = ["ls", "-la", "NULL"]
    t_redir redirs = NULL
}