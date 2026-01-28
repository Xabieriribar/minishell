#include "minishell.h"

static void print_init_list(t_token *head)
{
    while (head)
    {
        printf("%s\n", head->value);
        head = head->next;
    }
    printf("\n");
}
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
        {
            printf("%d %s[FAIL]%s\n", i, RED, RESET) ;
            print_init_list(head);
        }
        else
        {
            printf("%d %s[PASS]%s\n", i, GREEN, RESET);
            print_init_list(head);
        }
    }
    return (0);
}