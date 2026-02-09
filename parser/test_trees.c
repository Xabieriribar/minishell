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
    else
    {
        char **expected_arguments = ft_split(expected_args, ' ');
        int i = 0;
        int tree_args_len = 0;
        int expected_args_len = 0;
        while (tree->args[tree_args_len])
            tree_args_len++;
        while (expected_arguments[expected_args_len])
            expected_args_len++;
        if (expected_args_len != tree_args_len)
            return 1;
        while (tree->args[i])
        {
            if (strcmp(tree->args[i], expected_arguments[i]) != 0)
                return 1;
            i++;
        }
    }
    return 0;
}

int compare_redirs(char **redirs, t_node *tree)
{
    char *enum_type;
    if (!redirs)
        return 0;
    if (tree->redirs->redir_type == T_HEREDOC)
        enum_type = "T_HEREDOC";
    else if (tree->redirs->redir_type == T_REDIR_APPEND)
        enum_type = "T_REDIR_APPEND";
    else if (tree->redirs->redir_type == T_REDIR_IN)
        enum_type = "T_REDIR_IN";
    else if (tree->redirs->redir_type == T_REDIR_OUT)
        enum_type = "T_REDIR_OUT";
    if (strcmp(enum_type, redirs[0]))
        return 1;
    else if(strcmp(tree->redirs->filename, redirs[1]))
        return 1;
    return 0;
}

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
            printf("%s,", args[i]);
        i++;
    }
    printf("]\n");
}
int test_tree(int fd_tree_tester)
{
    int i = 1;
    t_token *head;
    char *line;
    int number_of_tokens;
    t_node *tree;
    while ((line = get_next_line(fd_tree_tester)))
    {
        char *tokens = strtok(line, "::");
        char *commands = strtok(NULL, "::");
        char **redirs = NULL;
        char *redir = strtok(NULL, "::");
        // if (strcmp(redir, "NULL") != 0)
        //     redirs = ft_split(redir, ',');
        if (strcmp(redir, "NULL") != 0)
            redirs = ft_split(redir, ',');
        head = init_list(tokens);
        tree = init_tree(head);
        number_of_tokens = ft_token_lstsize(head);
        if (compare_args(tree, commands, number_of_tokens) != 0)
            printf("%d %s[FAIL]%s\n", i, RED, RESET);
        else if (compare_redirs(redirs, tree) != 0)
            printf("%d %s[FAIL]%s\n", i, RED, RESET);
        else
            printf("%d %s[PASS]%s\n", i, GREEN, RESET);
        // // if (compare_redirs(tree, head) != 0)
        // //     printf("Redirs creation failed\n");
        // // if (compare_childs(tree, head) != 0)
        // //     printf("Child creation failed\n" != 0);
        i++;
        printf("ARGS: "), print_args(tree->args);
        free(line);
    }
    return 0;
}