#include "minishell.h"

int init_tree(t_token *token_list)
{
    t_node *node;
    if (ft_token_lstsize(token_list) == 1)
    {
        node = malloc(sizeof(struct s_node));
        if (!node)
            perror("Malloc failed for the node creation");
        node->args[0] = token_list->value;
        node->args[1] = NULL;
        node->redirs = NULL;
        node->left_child = NULL;
        node->right_child = NULL;
    }
    return 0;
}