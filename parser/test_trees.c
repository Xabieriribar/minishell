/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_trees.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:33:12 by rspinell          #+#    #+#             */
/*   Updated: 2026/02/23 13:50:56 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
void    compare_tree_args(t_node *tree, char *exp_arg, int nb_of_tok)
// {
//     if (tree->node_type != PIPE)
//     {
//         //COMPARE THEM
//         return;
//     }
//     compare_tree_args(tree->left_child, exp_arg)
//     compare_args(tree->left_child, exp_arg, nb_of_tok);
// }
int compare_args(t_node *tree, char *exp_arg, int nb_of_tok)
{
    if (!tree->args)
        return 1;
    if (!tree->args[0])
        return 1;
    if (nb_of_tok == 1)
    {
        if (strcmp(tree->args[0], exp_arg) != 0)
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
    printf("enum_type %s and filename %s\n", enum_type, tree->redirs->filename);
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
    if (!tree->args)
        tree = tree->left_child;
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
                printf("REDIR_TYPE %d: %s\n", j, find_enum_type(tree->redirs));
                printf("FILE NAME %d: %s\n", j, tree->redirs->filename);
            }
            tree->redirs = tree->redirs->next;
            j++;
        }
    }
}
// void assign_enums(char **expected_left_child, char **expected_right_child)
// {
//     if (*expected_left_child == T_PIPE)

// }
int compare_childs(char *exp_l_child, char *exp_r_child, t_node *tree)
{
    // enum right_type;
    // enum left_type;
    // assign_enums(&exp_l_child, &exp_r_child);
    
    (void)exp_l_child;
    (void)exp_r_child;
    if (tree->left_child != NULL || tree->left_child != NULL)
    {
        if (tree->left_child->node_type !=  PIPE
            && tree->right_child->node_type != COMMAND)
            return 1;
    }
    return 0;

}
void print_ast(t_node *node, int level)
{
    // 1. Caso base: si el nodo es NULL, no hay nada que imprimir
    if (!node)
        return;

    // 2. Recomendación visual: Imprime primero el hijo DERECHO
    // Esto hace que el árbol se vea correctamente de lado en la terminal
    print_ast(node->right_child, level + 1);

    // 3. Imprimir el nodo actual con su indentación
    // Usa un bucle simple para imprimir espacios o tabuladores según 'level'
    for (int i = 0; i < level; i++)
        printf("    "); // 4 espacios por nivel

    // 4. ¿Qué tipo de nodo es?
    if (node->node_type == PIPE)
        printf("[PIPE]\n");
    else if (node->node_type == COMMAND)
    {
        printf("CMD: ");
        // Aquí recorres tu array de argumentos que tanto te costó
        for (int i = 0; node->args && node->args[i]; i++)
            printf("%s ", node->args[i]);
        printf("\n");
    }

    // 5. Por último, el hijo IZQUIERDO
    print_ast(node->left_child, level + 1);
}
#include <ctype.h>
#include <string.h>

char *trim_whitespace(char *str)
{
    char *end;

    if (!str)
        return (NULL);

    // Trim leading space
    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0) // All spaces?
        return (str);

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Write new null terminator
    end[1] = '\0';

    return (str);
}
void serialize_tree(t_node *node, char *buffer)
{
    if (!node)
        return;

    if (node->node_type == PIPE)
    {
        strcat(buffer, "( ");
        serialize_tree(node->left_child, buffer);
        strcat(buffer, " | ");
        serialize_tree(node->right_child, buffer);
        strcat(buffer, " )");
    }
    else if (node->node_type == COMMAND)
    {
        strcat(buffer, "[");
        // 1. Añadir argumentos
        for (int i = 0; node->args && node->args[i]; i++)
        {
            strcat(buffer, node->args[i]);
            if (node->args[i + 1])
                strcat(buffer, " ");
        }
        
        // 2. Añadir redirecciones si existen
        t_redirs *r = node->redirs;
        while (r)
        {
            // Añadimos un espacio antes de la 
            // redirección para que no se pegue al comando
            strcat(buffer, " "); 
            if (r->redir_type == T_REDIR_IN) strcat(buffer, "<");
            else if (r->redir_type == T_REDIR_OUT) strcat(buffer, ">");
            else if (r->redir_type == T_REDIR_APPEND) strcat(buffer, ">>");
            else if (r->redir_type == T_HEREDOC) strcat(buffer, "<<");
            
            strcat(buffer, " ");
            strcat(buffer, r->filename);
            r = r->next;
        }
        strcat(buffer, "]");
    }
}
void run_tree_test(char *input_line)
{
    char *input = strtok(input_line, "::");
    char *expected = strtok(NULL, "::");
    if (!expected) return;

    // 1. Build your actual tree
    t_token *tokens = init_list(input);
    t_token *backup = tokens;
    t_node *tree = init_tree(&tokens);

    // 2. Create the "Actual" string
    char *actual = ft_calloc(16384, 1);
    if (tree)
        serialize_tree(tree, actual);

    // 3. Compare
    if (strcmp(actual, trim_whitespace(expected)) == 0)
        printf("[PASS] %s\n", input);
    else
    {
        printf("[FAIL] %s\n", input);
        printf("   Expected: %s\n", expected);
        printf("   Actual:   %s\n", actual);
    }
    if (backup)
        free_tokens(&backup);
    free(actual);
    if (tree)
        free_tree(tree);
}
int test_tree(int fd_tree_tester)
{
    char *line;
    while ((line = get_next_line(fd_tree_tester)))
    {
        run_tree_test(line);
        free(line);
    }
    return 0;
} */