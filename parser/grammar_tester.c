#include "minishell.h"


int test_grammar(int fd_grammar_tester)
{
    char *line_tokens;
    t_token *head;
    int i = 0;
    while ((line_tokens = get_next_line(fd_grammar_tester)))
    {
        char *cmd = strtok(line_tokens, "::");
        char *tokens = strtok(NULL, "::");
        (void)tokens;
        char *expected_result = strtok(NULL, "::");
        head = init_list(cmd);
        char *real_result = grammar_validator(head); 
        int result;
        i++;
        if ((result = strcmp(real_result, expected_result)) != 0)
            printf("%d %s[FAIL]%s %s\n", i, RED, RESET, head->value);
        else
            printf("%d %s[PASS]%s %s\n", i, GREEN, RESET, head->value);
    }
    return (0);
}