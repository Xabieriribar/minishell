#include "minishell.h"

int compare_args(t_node *tree, char *expected_args, int number_of_tokens)
{
    if (!tree->args[0])
        return 1;
    if (number_of_tokens == 1)
    {
        if (strcmp(tree->args[0], expected_args) != 0)
            return 1;
    }
    {
        char **expected_arguments = ft_split(expected_args, ' ');
        int i = 0;
        while (expected_arguments[i])
        {
            if (strcmp(tree->args[i], expected_arguments[i]) != 0)
            {
                printf("Here is %s and %s", tree->args[i], expected_arguments[i]);
                return 1;
            }
            i++;
        }
    }
    printf("Here then?\n");
    return 0;
}

// int compare_redirs(t_node *tree, t_token *token_head)
// {
//     if (strcmp(tree->redirs, token_head) != 0)
//         return 1;
//     return 0;
// }

// int compare_childs(t_node *tree, t_token *token_head)
// {
//     if (strcmp(tree, token_head) != 0)
//         return 1;
//     return 0;
// }
void    print_args(char **args)
{
    int i = 0;
    int mode = 1;
    while (args[i])
    {
        if (mode == 1)
        {
            printf("[%s,", args[i]);
            mode = 0;
        }
        else
            printf("%s", args[i]);
        i++;
    }
    printf("]\n");
}
int test_tree(int fd_tree_tester)
{
    int i = 1;
    char *line;
    t_token *head;
    int number_of_tokens;
    t_node *tree;
    while ((line = get_next_line(fd_tree_tester)))
    {
        char *commands = strtok(line, "::");
        head = init_list(commands);
        tree = init_tree(head);
        number_of_tokens = ft_token_lstsize(head);
        if (compare_args(tree, commands, number_of_tokens) != 0)
            return(printf("%d %s[FAIL]%s\n", i, RED, RESET), 1);
        else
            printf("%d %s[PASS]%s\n", i, GREEN, RESET);
        // // if (compare_redirs(tree, head) != 0)
        // //     printf("Redirs creation failed\n");
        // // if (compare_childs(tree, head) != 0)
        // //     printf("Child creation failed\n" != 0);
        i++;
        printf("ARGS: "), print_args(tree->args);
    }
    return 0;
}