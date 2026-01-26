#include "minishell.h"


int test_grammar(int fd_grammar_tester)
{
    char *line_tokens;
    t_token *head;
    while ((line_tokens = get_next_line(fd_grammar_tester)))
    {
        char *cmd = strtok(line_tokens, "::");
        char *tokens = strtok(NULL, "::");
        (void)tokens;
        char *expected_result = strtok(NULL, "::");
        head = init_list(cmd);
        char *real_result = grammar_validator(head); 
        int result;
        if ((result = strcmp(real_result, expected_result)) != 0)
            printf("FAIL\n");
        else
            printf("PASS\n");
    }
    return (0);
}