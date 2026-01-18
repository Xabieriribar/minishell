/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:26:09 by rick              #+#    #+#             */
/*   Updated: 2026/01/18 14:27:28 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to print a single token
void print_token(t_token *token)
{
    if (!token)
        return;
    printf("Index: %d | Type: %d | Value: '%s'\n", token->index, token->type, token->value);
}

// Function to print the entire linked list
void print_token_list(t_token *head)
{
    t_token *current = head;

    while (current)
    {
        print_token(current);
        current = current->next;
    }
}

// Test function
void test_init_list()
{
    char *line = "echo hello_world";
    t_token **head;

    head = init_list(line);
    if (!head)
    {
        printf("Failed to initialize token list.\n");
        return;
    }
    printf("Token list:\n");
    print_token_list(*head);
    free_tokens(head);
}
