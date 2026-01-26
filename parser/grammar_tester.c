#include "minishell.h"

int test_grammar(int fd_grammar_tester)
{
    char *line_tokens;
    t_token *head;
    while ((line_tokens = get_next_line(fd_grammar_tester)))
    {
        char *cmd = strtok(line_tokens, "::");
        char *tokens = strtok(NULL, "::");
        char **token = ft_split(tokens, ' ');
        char *result = strtok(NULL, "::");
        head = init_list(cmd);
        int i = 0;
        while (head)
        {
            if (strcmp(head->, token[i]))
            head = head->next;
        }
        head = init_list(line_tokens);

    }
    return (0);
}`