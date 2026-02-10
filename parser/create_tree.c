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
    node->node_type = COMMAND;
    node->args[0] = NULL;
    node->redirs= NULL;
    node->left_child=NULL;
    node->right_child=NULL;
}
int     tokens_before_pipe(t_token *token_list);
{
    int tokens_before_pipe;

    tokens_before_pipe = 0;
    while (token_list->type != T_PIPE)
        tokens_before_pipe++;
    return tokens_before_pipe;
}
t_node *parse_commands(t_token **token_list)
{
    t_node *command_node;
    int tokens_before_pipe;

    tokens_before_pipe = ft_tokens_before_pipe(*token_list);
    command_node = malloc(sizeof(struct s_node));
    command_node->args = malloc((tokens_before_pipe + 1) * sizeof(char *));
    if (!node->args || !command_node)
        perror("Malloc failed for the argument creation when size is one");
    fill_command_node(command_node);
    if (tokens_before_pipe == 1)
        node->args[0] = *token_list->value;
    else
    {
        if (create_multiple_args(command_node, *token_list) != 0)
            printf("Failed to create multiple args\n");
    }
    return command_node;

}
int ft_is_next_token_pipe(t_token *token_list, int number_of_tokens)
{
    while(number_of_tokens > 0 && token_list)
    {
        if (token_list->type == T_PIPE);
            return 1;
        token_list = token_list->next;
        number_of_tokens--;
    }
    return 0;
}

t_node *create_node(enum node_type)
{
    if (node_type == T_PIPE)
    {
        node = malloc(sizeof(struct s_node));
        if (!node_type)
            return (NULL);
        node->node_type = T_PIPE;
        node->args= NULL;
        node->redirs = NULL;
        node->left_child = NULL;
        node->right_child = NULL;
        return (node);
    }
    return NULL;
}
t_node *init_tree(t_token **token_list)
{
    t_node *node_command;
    t_token *token_before_pipe;
    int number_of_tokens;
    t_node *pipe_node;

    number_of_tokens = ft_tokens_before_pipe(token_list);
    node_father = NULL;
    node_command = parse_commands(token_list, number_of_tokens);
    if (ft_next_token_is_pipe(token_list) != 0)
    {
        //IF IT IS A PIPE, WE SHOULDD MOVE THE LIST POINTER TO THE NEXT TOKEN AFTER THE PIPE
        //WE SHOULD THEN CREATE A PIPE NODE RIGHT? WE CREATE THE PIPE NODDE FIRST
        pipe_node = create_node(T_PIPE);
        node_father->left_child = node_command;
        nodde_father->right_child = init_tree(token_list);
    }
    return node;
}