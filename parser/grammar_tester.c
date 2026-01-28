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
        if (i == 47)
            printf("LSTSIZE %d\n", ft_token_lstsize(head));
        if ((result = strcmp(real_result, expected_result)) != 0)
            printf("%d %s[FAIL]%s\n", i, RED, RESET, test_init_list(cmd, NULL));
        else
            printf("%d %s[PASS]%s %s\n", i, GREEN, RESET, test_init_list(cmd, NULL));
    }
    return (0);
}