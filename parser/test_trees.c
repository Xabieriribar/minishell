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

char *find_enum_type(t_redirs *redirs)
{
    char *enum_type;
    enum_type = NULL;
    if (redirs->redir_type == T_HEREDOC)
        enum_type = "T_HEREDOC";
    else if (redirs->redir_type == T_REDIR_APPEND)
        enum_type = "T_REDIR_APPEND";
    else if (redirs->redir_type == T_REDIR_IN)
        enum_type = "T_REDIR_IN";
    else if (redirs->redir_type == T_REDIR_OUT)
        enum_type = "T_REDIR_OUT";
    return enum_type;
}

int compare_redirs(char **redirs, t_node *tree, t_token *token_list)
{
    char *enum_type = NULL;
    if (!redirs)
        return 0;
    int number_of_redirs = find_number_of_redirs(token_list);
    if (number_of_redirs < 2)
    {
        enum_type = find_enum_type (tree->redirs);
        redirs = ft_split(redirs[0], ',');
        if (strcmp(enum_type, redirs[0]) != 0)
            return 1;
        else if(strcmp(tree->redirs->filename, redirs[1]) != 0)
            return 1;
    }
    else
    {
        int i = 0;
        while (redirs[i])
        {
            char **redir_and_filename = ft_split(redirs[i], ',');
            enum_type = find_enum_type(tree->redirs);
            int j = 0;
            if (strcmp(enum_type, redir_and_filename[j]) != 0)
                return 1;
            else if(strcmp(tree->redirs->filename, redir_and_filename[j + 1]) != 0)
                return 1;
            i++;
            tree->redirs = tree->redirs->next;

        }
    }
    return 0;
}

// int compare_childs(t_node *tree, t_token *token_head)
// {
//     if (strcmp(tree, token_head) != 0)
//         return 1;
//     return 0;
// }
void    print_tree(t_node *tree)
{
    int i = 0;
    printf("ARGS: [");
    while (tree->args[i])
    {
        printf("%s", tree->args[i]);
        if (tree->args[i + 1] != NULL)
            printf(",");
        i++;
    }
    printf("]\n");
    int mode = 1;
    if (tree->redirs != NULL)
    {
        printf("Problemon");
        while(tree->redirs)
        {
            int j = 1;
            if (mode == 1)
            {
                printf("REDIR_TYPE %d: %s\n", j, find_enum_type(tree->redirs));
                printf("FILE NAME %d: %s\n", j, tree->redirs->filename);
                mode = 0;
            }
            else
            {
                printf("REDIR_TYPE %d: %s\n", j, find_enum_type(tree->redirs->next));
                printf("FILE NAME %d: %s\n", j, tree->redirs->next->filename);
            }
            tree->redirs = tree->redirs->next;
            j++;
        }
    }
}
int test_tree(int fd_tree_tester)
{
    int i = 1;
    t_token *token_list;
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
            redirs = ft_split(redir, '-');
        token_list = init_list(tokens);
        tree = init_tree(token_list);
        t_node *temp_tree = tree;
        number_of_tokens = ft_token_lstsize(token_list);
        if (compare_args(tree, commands, number_of_tokens) != 0)
            printf("%d %s[FAIL]%s\n", i, RED, RESET);
        else if (compare_redirs(redirs, tree, token_list) != 0)
            printf("%d %s[FAIL]%s\n", i, RED, RESET);
        else
            printf("%d %s[PASS]%s\n", i, GREEN, RESET);
        // // if (compare_redirs(tree, head) != 0)
        // //     printf("Redirs creation failed\n");
        // // if (compare_childs(tree, head) != 0)
        // //     printf("Child creation failed\n" != 0);
        i++;
        print_tree(temp_tree);
        free(line);
    }
    return 0;
}