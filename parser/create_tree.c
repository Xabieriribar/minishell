#include "minishell.h"

void    create_redirs_list(t_node *node, t_token *pointer_to_redir_token)
{
    if (!node->redirs)
    {
        node->redirs = malloc(sizeof(struct s_redirs));
        node->redirs->redir_type = pointer_to_redir_token->type;
        node->redirs->filename = pointer_to_redir_token->next->value;
        node->redirs->next = NULL;
    }
    else
    {
        while (node->redirs->next != NULL)
            node->redirs = node->redirs->next;
        node->redirs->next = malloc(sizeof(struct s_redirs));
        node->redirs->next->filename = pointer_to_redir_token->next->value;
        node->redirs->next->redir_type = pointer_to_redir_token->type;
    }
}
int     create_multiple_args(t_node *node, t_token *token_list)
{
    int index;
    index = 0;
    if (!node || !token_list)
        return 1;
    while (token_list)
    {
        if (ft_is_redir(token_list->type) == 0)
        {
            create_redirs_list(node, token_list);
            token_list = token_list->next->next;
            continue;
        }
        node->args[index] = token_list->value;
        token_list = token_list->next;
        index++;
    }
    node->args[index] = NULL;
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
    node = malloc(sizeof(struct s_node));
    node->args = malloc((number_of_tokens + 1) * sizeof(char *));
    fill_tree(node);
    if (!node->args || !node)
        perror("Malloc failed for the argument creation when size is one");
    if (number_of_tokens == 1)
        node->args[0] = token_list->value;
    else
    {
        if (create_multiple_args(node, token_list) != 0)
            printf("Failed to create multiple args\n");
    }
    return node;
}