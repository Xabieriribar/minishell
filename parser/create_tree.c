#include "minishell.h"

int     create_multiple_args(t_node *node, t_token *token_list)
{
    int index;
    index = 0;
    if (!node || !token_list)
        return 1;
    while (token_list)
    {
        node->args[index] = token_list->value;
        token_list = token_list->next;
        index++;
    }
    return 0;
}
void    fill_tree(t_node *node)
{
    node->args[0] = NULL;
    node->redirs= NULL;
    node->left_child=NULL;
    node->right_child=NULL;
}
t_node *init_tree(t_token *token_list)
{
    t_node *node;
    int number_of_tokens;

    number_of_tokens = ft_token_lstsize(token_list);
    node = malloc(sizeof(struct s_node) * number_of_tokens);
    node->args = malloc(number_of_tokens * sizeof(node->args));
    fill_tree(node);
    if (!node->args || !node)
        perror("Malloc failed for the argument creation when size is one");
    if (number_of_tokens == 1)
        node->args[0] = token_list->value;
    else
        if (create_multiple_args(node, token_list) != 0)
            printf("Failed to create multiple args\n");
    return node;
}