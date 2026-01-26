#include "minishell.h"

char *grammar_validator(t_token *head)
{
    if (ft_token_lstsize(head) == 1 && head->type == T_WORD)
        return ("PASS\n");
    return ("UNKNOWN BEHAVIOR");
}