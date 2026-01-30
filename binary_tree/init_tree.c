/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:22:34 by rick              #+#    #+#             */
/*   Updated: 2026/01/30 17:45:47 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
parse(tokens):
    return parse_pipeline(tokens)
    
4. Pipeline parser (creates the AST)
parse_pipeline(tokens):
    left = parse_command(tokens)

    while current_token(tokens) == PIPE:
        consume_token(tokens)        // '|'
        right = parse_command(tokens)

        pipe_node = new AST Node
        pipe_node.type = PIPE
        pipe_node.left = left
        pipe_node.right = right

        left = pipe_node

    return left
5. Command parser (collect argv + redirs)
parse_command(tokens):
    cmd = new AST Node
    cmd.type = COMMAND

    while tokens not empty and current_token != PIPE:
        if current_token == WORD:
            append cmd.argv with token.lexeme
            consume_token(tokens)

        else if current_token is REDIRECTION:
            parse_redirection(cmd, tokens)

        else:
            syntax_error

    return cmd
6. Redirection parser
parse_redirection(cmd, tokens):
    redir = new Redirection
    redir.type = current_token.type
    consume_token(tokens)           // '<', '>', '>>', '<<'

    if current_token != WORD:
        syntax_error

    redir.target = token.lexeme
    consume_token(tokens)

    append cmd.redirs with redir */

bool	is_redir(t_token *token)
{
	if (token->type == T_REDIR_IN
		|| token->type == T_REDIR_OUT
		|| token->type == T_REDIR_APPEND
		|| token->type == T_HEREDOC)
		return (true);
	return (false);
}

/*
* Adds a redir to the last position of the list*/
void	lst_add_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	if (!new)
		return ;
	new->next = NULL;
	ptr = lstlast_redir(*lst);
	if (!ptr)
	{
		*lst = new;
		return ;
	}
	ptr->next = new;
}

/* 
* Returns a pointer to the last element of the list */
t_redir	*lstlast_redir(t_redir *lst)
{
	t_redir	*ptr;

	ptr = lst;
	if (!lst)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

/*
* Function to add a redirection to the linked list of 
* redirs inside a command node. 
- Allocates memory for the new redir and for the string value.*/
void	append_redir(t_node *node, t_token *token)
{
	t_redir *new;

	if (!token || !node)
		return (NULL);
	new = ft_calloc(sizeof(t_redir), 1);
	if (!new)
		return (perror("Err: Malloc"), NULL);
	new->type = token->type;
	new->target = ft_strdup(token->next->value);
	if (!new->target)
		return (free(new), perror("Err: Malloc"), NULL);
	new->next = NULL;
	lst_add_back_redir(&(node->redirs), new);
}

/*
* Init a node comand to all null.*/
t_node	*init_node_cmd(void)
{
	t_node  *node;

	node = ft_calloc(sizeof(t_node), 1);
    if (!node)
        return (perror("Err: Malloc"), NULL);
    node->type = T_CMD;
	node->argv = NULL;
	node->left = NULL;
	node->redirs = NULL;
	node->right = NULL;
}

/*
* Frees an array of strings. */
void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/*
* Function creates or reallocates an array of strings argv
* inside the node t_node, and adds a new arguent being the
* value of the token.*/
void	add_args(t_node *node, t_token *token)
{
	char	**arr;
	int		i;

	if (!token || !node)
		return (NULL);
	i = 0;
	if (node->argv)
	while (node->argv[i])
		i++;
	arr = ft_calloc(sizeof(char *), i + 2);
	i = 0;
	while (node->argv[i++])
	{
		arr[i] = ft_strdup(node->argv[i]);
		if (!arr[i])
			return (free_tab(arr), NULL);
	}
	arr[i] = ft_strdup(token->value);
	if (!arr[i])
		return (free_tab(arr), NULL);
	i++;
	arr[i] = NULL;
	free_tab(node->argv);
	node->argv = arr;
}

/*
* Function initializes a new node CMD, and iterates in the list
* of tokens, adding the values of each token in the array of
* argv[] or appending a redirection in the linked list 
* t_redir redirs inside the node.*/
t_node  *make_node_cmd(t_token *token)
{
	t_node	*node;

	if (!token)
		return (perror("Err: No token recieved"), NULL);
	node = init_node_cmd();
	if (!node)
		return (perror("Err: Malloc"), NULL);
	while (token->type != T_PIPE || token == NULL)
	{
		if (is_redir(token))
		{
			append_redir(node, token);
			if (!node->redirs)
				return (free_node(node), NULL);
			token = token->next;
		}
		else
		{
			if (!node->argv)
				init_args()
			else
				add_args(node, token);
			if (!node->argv)
				return (free_node(node), NULL);
		}
		token = token->next;
	}
	return (node);
}


