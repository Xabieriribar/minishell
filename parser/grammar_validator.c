#include "minishell.h"


int  ft_check_pipes(t_token *head)
{
    int lst_len = ft_token_lstsize(head);
    int lst_index = 1;
    if (head->type == T_PIPE)
        return (1);
    while (head)
    {
        if (head->type == T_PIPE)
        {
            if (lst_len == lst_index)
                return (1);
            else if (head->next->type == T_PIPE)
                return (1);
        }
        lst_index++;
        head = head->next;
    }
    return (0);
}
int ft_check_simple_commands(t_token *head)
{
    while (head)
    {
        if (head->type != T_WORD)
            return (1);
        head = head->next;
    }
    return (0);
}

int ft_check_redirs(t_token *head)
{
    int lst_len = ft_token_lstsize(head);
    int  lst_index = 1;
    while (head)
    {
        if (ft_is_redir(head->type) == 0)
        {
            if (ft_is_append_or_heredoc(head->type) != 0)
            {
                if (head->prev->type == T_WORD || head->prev->type != T_PIPE)
                    return (1); //HERE WE SHOW A PARSE ERROR NEAR << OR >>
            }
            else if (lst_len == lst_index)
                return (1);
            else if (head->next->type != T_WORD)
                return (printf("syntax error near unexpected token `newline'\n"), 1); //HERE WE SHOW A PARSE ERORR NEAR \N TOKEN
        }
        lst_index++;
        head = head->next;
    }
    return (0);
}


char *grammar_validator(t_token *head)
{
    if (ft_check_simple_commands(head) == 0)
        return ("PASS\n");
    else if (ft_check_pipes(head) != 0)
        return ("FAIL\n");
    else if (ft_check_redirs(head) != 0)
        return ("FAIL\n");
    // else if (ft_check_pipes(head) != 0)
    //     return ("FAIL\n");
    return ("PASS\n");
}