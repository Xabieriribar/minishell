#include "minishell.h"

/*THIS FUNCTION MUST BE CALLED BEFORE EXECUTE_PIPELINE IS CALLED. WHY? WE MUST FILL THE TEMPORARY
FILE DESCRIPTOR OF HEREDOC WHEN FINDING IT, LIKE THIS, WE DONT OVERCOMPLICATE OUR LIFE ON THE MAIN
EXECUTOR*/

char    *finds_directory(char *command, char *path)
{
    char **directories_to_check;
    int index;
    char *result;

    index = 0;
    directories_to_check = ft_split(path, ":");
    while (directories_to_check[index])
    {
        result = ft_strjoin(directories_to_check[index], "/");
        if (!result)
            return (free_splits(directories_to_check, index), NULL);
        result = ft_strjoin(result, command);
        if (!result)
            return (free_splits(directories_to_check, index), NULL);
        if (access(result, F_OK | X_OK) != -1)
            return (result);
        free(result);
        index++;
    }
    return (free_splits(directories_to_check, index), NULL);
}

char    *get_path(char *command, char *path)
{
    char    *result;
    int     index;

    index = 0;
    if (!path || !command)
        return (NULL);
    if (contains_slash(command))
    {
        if (!can_access(command, result))
            return (NULL);
        return (result);
    }
    result = finds_directory(command, path);
    if (!result)
        return (NULL);
    return (result);
}

void    execute_command(t_node *tree, t_env *env_var, int fd_in, int fd_out)
{
    t_env   *path_env_var;
    char    **env_var;
    char    *pathname;

    if (tree->redirs != NULL)
        update_fd(tree->redirs, &fd_in, &fd_out);
    dup2(fd_in, 0);
    dup2(fd_out, 1);
    close_if_not_stdin_or_stdout(fd_in, fd_out);
    path_env_var = return_path_node(env_var);
    if (!path_env_var)
        perror("Environment variable path doesnt exist");
    pathname = get_path(tree->args[0], path_env_var);
    if (!pathname)
        exit(127);
    env_var = convert_env_var_to_array(data->env, ft_env_var_lstsize(env_var)); 
    if (execve(pathname, tree->args, env_var) != -1)
    {
        free(pathname);
        free_splits(env_var, ft_env_var_lstsize(env_var));
        perrror("Execve failed to execute");
    }
    exit(1);
}

void    wait_for_last_child(t_data *data)
{
    int index;

    index = 0;
    while (index < data->(*pid_count))
    {
        waitpid(data->pid_values[index], data->(&status), 0);
        if (WIFEXITED(data->status))
            data->status = WEXITSTATUS(data->status);
        index++;
    }
}
void    execute_pipeline(t_node *tree, int fd_in, int fd_out, t_data *data)
{
    pid_t   process_id;
    t_env   *env_linked_list;
    int     pipefdes[2];

    if (tree->node_type == COMMAND)
    {
        process_id = fork();
        if (process_id == 0)
            execute_command(tree, env_linked_list, fd_in, fd_out);
        if (fd_in != 0)
            close(fd_in);
        if (fd_out != 1)
            close(fd_out);
        data->pid_values[data->(*pid_count++)] = process_id;
        return ;
    }
    else
    {
        if (pipe(pipefdes) < 0)
            perror("First pipe failed to execute");
        exeucte_pipeline(tree->left_child, fd_in, pipefdes[1]);
        execute_pipeline(tree->right_child, pipefdes[0], fd_out);
        wait_for_last_child(data);
    }
}