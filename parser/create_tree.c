#include "minishell.h"

t_node *init_tree(t_token *token_list)
{
    t_node *node;
    int number_of_tokens;

    number_of_tokens = ft_token_lstsize(token_list);
    node = ft_calloc(number_of_tokens, sizeof(struct s_node));
    node->args = ft_calloc(number_of_tokens, sizeof(node->args));
    if (!node->args)
        perror("Malloc failed for the argument creation when size is one");
    // node->args[0] = NULL;
    // fill_tree_values(node);
    if (!node)
        perror("Malloc failed for the node creation");
    // if (number_of_tokens == 1)
    // {
    //     node->args[0] = token_list->value;
    //     node->args[1] = NULL;
    //     node->redirs = NULL;
    //     node->left_child = NULL;
    //     node->right_child = NULL;
    // }
    return node;
}