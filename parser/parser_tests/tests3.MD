RED_IN WORD WORD (command < infile cat)
Result:
typedef struct s_node {
    t_type node = CMD_NODE
    t_node *left = NULL
    t_node *right = NULL
    t_node *child = NULL
    char **args = ["cat", "NULL"]
    t_redir redir= ADDRESS OF THE LINKED LIST
}

typedef struct t_redir {
    t_type type = T_REDIR_IN
    char *filename = "infile"
}