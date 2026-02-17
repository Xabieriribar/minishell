#include "minishell.h"


int ft_check_simple_commands(t_token *head)
{
    int no_word_len;
/*     int lst_len;

    lst_len = ft_token_lstsize(head); */
    no_word_len = 0;
    while (head)
    {
        if (head->type != T_WORD)
            no_word_len++;
        head = head->next;
    }
    if (no_word_len != 0)
        return (1);
    return (0);
}

int  ft_check_pipes(t_token *head)
{
    int lst_len = ft_token_lstsize(head);
    int lst_index = 1;
    if (head->type == T_PIPE)
        return (printf("parse error near '|'\n"), 1);
    while (head)
    {
        if (head->type == T_PIPE)
        {
            if (lst_len == lst_index)
                return (printf("parse error near '|'\n"), 1);
            else if (head->next->type == T_PIPE)
                return (printf("parse error near '|'\n"), 1);
            else if (head->prev->type == T_REDIR_IN)
                return (printf("parse error near '|'\n"));
        }
        lst_index++;
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
            if (lst_len == lst_index)
                return (printf("parse error near 'newline'\n"), 1); //HERE WE SHOW A PARSE ERORR NEAR \N TOKEN
            else if (head->next->type != T_WORD)
            {
                if (head->next->type == T_REDIR_APPEND)
                    return (printf("parse error near '>>'\n"), 1);
                else if (head->next->type == T_HEREDOC)
                    return (printf("parse error near '<<'\n"), 1);
                else if (head->next->type != T_HEREDOC && head->next->type != T_REDIR_APPEND)
                    return (printf("parse error near '|'\n"), 1);
            }
            else if (ft_is_append_or_heredoc(head->type) != 0)
            {
                if (head->prev->type != T_WORD)
                    return (printf("syntax error near unexpected token '<<'\n"),1); //HERE WE SHOW A PARSE ERROR NEAR << OR >>
            }
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
#include "minishell.h"


int ft_check_simple_commands(t_token *head)
{
    int no_word_len;
    int lst_len;

    lst_len = ft_token_lstsize(head);
    no_word_len = 0;
    while (head)
    {
        if (head->type != T_WORD)
            no_word_len++;
        head = head->next;
    }
    if (no_word_len != 0)
        return (1);
    return (0);
}

int  ft_check_pipes(t_token *head)
{
    int lst_len = ft_token_lstsize(head);
    int lst_index = 1;
    if (head->type == T_PIPE)
        return (printf("parse error near '|'\n"), 1);
    while (head)
    {
        if (head->type == T_PIPE)
        {
            if (lst_len == lst_index)
                return (printf("parse error near '|'\n"), 1);
            else if (head->next->type == T_PIPE)
                return (printf("parse error near '|'\n"), 1);
            else if (head->prev->type == T_REDIR_IN)
                return (printf("parse error near '|'\n"));
        }
        lst_index++;
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
            if (lst_len == lst_index)
                return (printf("parse error near 'newline'\n"), 1); //HERE WE SHOW A PARSE ERORR NEAR \N TOKEN
            else if (head->next->type != T_WORD)
            {
                if (head->next->type == T_REDIR_APPEND)
                    return (printf("parse error near '>>'\n"), 1);
                else if (head->next->type == T_HEREDOC)
                    return (printf("parse error near '<<'\n"), 1);
                else if (head->next->type != T_HEREDOC && head->next->type != T_REDIR_APPEND)
                    return (printf("parse error near '|'\n"), 1);
            }
            else if (ft_is_append_or_heredoc(head->type) != 0)
            {
                if (head->prev->type != T_WORD)
                    return (printf("syntax error near unexpected token '<<'\n"),1); //HERE WE SHOW A PARSE ERROR NEAR << OR >>
            }
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