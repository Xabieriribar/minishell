WORD WORD RED_OUT WORD (command echo hello > outfile)
Result:
typedef struct s_node {
    t_type node = CMD_NODE
    t_node *left = NULL
    t_node *right = NULL
    t_node *child = NULL
    char **args = ["echo", "hello", NULL]
    t_redir redir= ADDRESS OF THE LINKED LIST
}

typedef struct t_redir {
    t_type type = T_REDIR_OUT
    char *filename = "outfile"
}