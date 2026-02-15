
#include "minishell.h"
int execute_pipeline(t_node *tree)
{
    pid_t   fork_value_left;
    pid_t   fork_value_right;
    int     pipefdes[2];
    char    *pathname;
    int     call_fork_twice;

    if (tree->left_child->node_type == COMMAND)
    {
        // pathname = search_path();
        // execve()
    }
    else
    {
        call_fork_twice = 2;
        while (call_fork_twice)
        {
            fork_value_left = fork();
            fork_value_right = fork();
            if (fork_value_left < 0 || fork_value_right < 0)
                perror("Fork function call failed");
            if (fork_value_left == 0)
            {
                if (pipe(pipefdes) < 0)
                    perror("Pipe function call failed");
                close(pipefdes[0]);
                dup2(pipefdes[1], 1);
                execute_pipeline

            }
            if (fork_value_right == 0)
            call_fork_twice--;
        }
    }

}