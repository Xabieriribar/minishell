#include "minishell.h"

void    create_redirs_list(t_node *node, t_token *pointer_to_redir_token)
{
    t_redirs *new_node;

    if (!node->redirs)
        node->redirs = ft_lstnew_redirs(pointer_to_redir_token->next->value, pointer_to_redir_token->type);
    else
    {
        new_node = ft_lstnew_redirs(pointer_to_redir_token->next->value, pointer_to_redir_token->type); 
        ft_lstadd_back_redirs(&(node->redirs), new_node);
    }
}
int     create_multiple_args(t_node *node, t_token *token_list)
{
    int index;
    index = 0;
    if (!node || !token_list)
        return 1;
    while (token_list && token_list->type != T_PIPE)
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

void    fill_command_node(t_node *node)
{
    node->node_type = COMMAND;
    node->args[0] = NULL;
    node->redirs= NULL;
    node->left_child=NULL;
    node->right_child=NULL;
}
int     ft_tokens_before_pipe(t_token *token_list)
{
    int tokens_before_pipe;
    int pipe_found;

    pipe_found = 0;
    tokens_before_pipe = 0;
    while (token_list)
    {
        if (token_list->type != T_PIPE)
            tokens_before_pipe++;
        else
            pipe_found = 1;
        if (pipe_found == 1)
            return tokens_before_pipe;
        token_list = token_list->next;
    }
    return tokens_before_pipe;
}
int move_pointer_to_next_pipe(t_token **token_list)
{
    while (*token_list)
    {
        if ((*token_list)->type == T_PIPE)
            return 1;
        *token_list = (*token_list)->next;
    }
    return 0;
}
t_node *parse_commands(t_token **token_list)
{
    t_node *command_node;
    int tokens_before_pipe;

    tokens_before_pipe = ft_tokens_before_pipe(*token_list);
    command_node = malloc(sizeof(struct s_node));
    command_node->args = malloc((tokens_before_pipe + 1) * sizeof(char *));
    if (!command_node->args || !command_node)
        perror("Malloc failed for the argument creation when size is one");
    fill_command_node(command_node);
    if (tokens_before_pipe == 1)
        command_node->args[0] = (*token_list)->value;
    else
    {
        if (create_multiple_args(command_node, *token_list) != 0)
            printf("Failed to create multiple args\n");
    }
    move_pointer_to_next_pipe(token_list);
    return command_node;

}

int ft_next_token_is_pipe(t_token **token_list)
{
    if (!*token_list)
        return 0;
    if ((*token_list)->type == T_PIPE)
        return 1;
    return 0;
}

t_node *create_node(t_type node_type)
{
    t_node *node;

    // node->left_child = NULL;
    // node->right_child = NULL;
    // node->redirs = NULL;
    // node->args = NULL;
    if (node_type == T_PIPE)
    {
        node = malloc(sizeof(struct s_node));
        if (!node)
            return (NULL);
        node->node_type = PIPE;
        node->args= NULL;
        node->redirs = NULL;
        node->left_child = NULL;
        node->right_child = NULL;
        return (node);
    }
    return NULL;
}
int     move_pointer_after_pipe(t_token **token_list)
{
    *token_list = (*token_list)->next;
    return 0;
}
t_node *init_tree(t_token **token_list)
{
    t_node *node_command;
    t_node *pipe_node;

    node_command = parse_commands(token_list);
    if (ft_next_token_is_pipe(token_list) != 0)
    {
        pipe_node = create_node(T_PIPE);
        move_pointer_after_pipe(token_list);
        pipe_node->right_child = node_command;
        pipe_node->left_child = init_tree(token_list);
        return pipe_node;
    }
    return node_command;
}