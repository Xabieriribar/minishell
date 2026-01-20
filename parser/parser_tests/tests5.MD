RED_IN WORD WORD WORD PIPE WORD WORD RED_OUT WORD (Command: < infile grep "hello" | wc -l > outfile)
Result:
typedef struct s_node {
    t_type node = CMD_PIPE
    t_node *left = address of the grep "hello" command node with a linked list of one element with red_in
    t_node *right = address of the wc -l command node with a linked list of a single node called outfile 
    t_node *child = NULL
    char **args = NULL
    t_redir redir = NULL
}
