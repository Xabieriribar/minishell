#include "minishell.h"

int compare_args(t_node *tree, char *expected_args)
{
    if (strcmp(tree->args[0], expected_args) != 0)
        return 1;
    return 0;
}

int compare_redirs(t_node *tree, t_token *token_head)
{
    if (strcmp(tree, token_head) != 0)
        return 1;
    return 0;
}

int compare_childs(t_node *tree, t_token *token_head)
{
    if (strcmp(tree, token_head) != 0)
        return 1;
    return 0;
}
int test_tree(int fd_tree_tester)
{
    char *line;
    t_token *head;
    t_node *tree;
    while ((line = get_next_line(fd_tree_tester)))
    {
        char *commands = strtok(line, "::");
        head = init_list(commands);

        tree = init_tree(head);

        if (compare_args(tree, line) != 0)
            printf("Argument creation failed\n");
        // if (compare_redirs(tree, head) != 0)
        //     printf("Redirs creation failed\n");
        // if (compare_childs(tree, head) != 0)
        //     printf("Child creation failed\n" != 0);
    }
}