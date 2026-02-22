#include "minishell.h"

/*THIS FUNCTION MUST BE CALLED BEFORE EXECUTE_PIPELINE IS CALLED. WHY? WE MUST FILL THE TEMPORARY
FILE DESCRIPTOR OF HEREDOC WHEN FINDING IT, LIKE THIS, WE DONT OVERCOMPLICATE OUR LIFE ON THE MAIN
EXECUTOR*/

char    *finds_directory(char *command, char *path)
{
    char **directories_to_check;
    int index;
    char *result;
    char    *temp;

    index = 0;
    directories_to_check = ft_split(path, ':');
    while (directories_to_check[index])
    {
        temp = ft_strjoin(directories_to_check[index], "/");
        if (!temp)
            return (free_splits(directories_to_check, index), NULL);
        result = ft_strjoin(temp, command);
        free(temp);
        if (!result)
            return (free_splits(directories_to_check, index), NULL);
        if (access(result, F_OK | X_OK) != -1)
            return (free_splits(directories_to_check, index), result);
        free(result);
        index++;
    }
    return (free_splits(directories_to_check, index), NULL);
}

char    *get_path(char *command, char *path)
{
    char    *result;

    if (!path || !command)
        return (NULL);
    result = NULL;
    if (contains_slash(command))
    {
        result = can_access(command);
        if (!result)
            return (NULL);
        return (result);
    }
    result = finds_directory(command, path);
    if (!result)
        return (NULL);
    return (result);
}

void    write_error_message(char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
}

void    handle_pathname_error_message(char *pathname, char *cmd, t_data *data)
{
    struct  stat st;

    if (ft_strncmp(cmd, "..", 2) == 0)
    {
        ft_putstr_fd("minishell: ..: command not found\n", 2);
        free_all_and_exit(data, 127);
    }
    if (ft_strncmp(cmd, ".", 1) == 0)
    {
        ft_putstr_fd("minishell: .: filename argument required\n", 2);
        free_all_and_exit(data, 2);
    }
    if (!pathname)
    {
        write_error_message(cmd);
        ft_putstr_fd(": command not found\n", 2);
        free_all_and_exit(data, 127);
    }
    if (stat(pathname, &st) == 0)
    {
        if (S_ISDIR(st.st_mode))
        {
            write_error_message(cmd);
            ft_putstr_fd(": Is a directory\n", 2);
            free_all_and_exit(data, 126);
        }
        if (access(pathname, X_OK) == -1)
        {
            write_error_message(cmd);
            ft_putstr_fd(": Permission denied\n", 2);
            free_all_and_exit(data, 126);
        }
    }
}
void    execute_command(t_node *tree, t_data *data, int fd_in, int fd_out)
{
    t_env   *path_env_var;
    char    **env_vars;
    char    *pathname;

    close_if_not_stdin_or_stdout(fd_in, fd_out);
    path_env_var = return_path(data->env_var);
    if (!path_env_var)
        perror("Environment variable path doesnt exist");
    pathname = get_path(tree->args[0], path_env_var->value);
    handle_pathname_error_message(pathname, tree->args[0], data);
    env_vars = convert_env_var_to_array(data->env_var, ft_env_var_lstsize(data->env_var)); 
    if (execve(pathname, tree->args, env_vars) != -1)
    {
        free(pathname);
        free_splits(env_vars, ft_env_var_lstsize(data->env_var));
        perror("Execve failed to execute");
        exit(127);
    }
    exit(1);
}

void    wait_for_last_child(t_data *data)
{
    int index;

    index = 0;
    while (index < data->pid_count)
    {
        waitpid(data->pid_values[index], &(data->exit_status), 0);
        if (WIFEXITED(data->exit_status))
            data->exit_status= WEXITSTATUS(data->exit_status);
        index++;
    }
}
void    execute_pipeline(t_node *tree, int fd_in, int fd_out, t_data *data)
{
    pid_t   process_id;
    int     pipefdes[2];
    int     i;

    (void)i;
    if (tree->node_type == COMMAND)
    {
        process_id = fork();
        if (process_id == 0)
        {
            if (tree->redirs != NULL)
                update_fd(tree->redirs, &fd_in, &fd_out, 0);
            dup2(fd_in, 0);
            dup2(fd_out, 1);
            i = 3;
            while (i < 1024)
                close(i++);
            if (!tree->args || !tree->args[0])
                exit(EXIT_SUCCESS);
            if (run_bultins(tree->args, &(data->env_var), &data, fd_out) != -1)
                exit(EXIT_SUCCESS);
            execute_command(tree, data, fd_in, fd_out);
        }
        if (fd_in != 0)
            close(fd_in);
        if (fd_out != 1)
            close(fd_out);
        data->pid_values[data->pid_count] = process_id;
        data->pid_count++;
        return ;
    }
    else
    {
        if (pipe(pipefdes) < 0)
            perror("First pipe failed to execute");
        execute_pipeline(tree->left_child, fd_in, pipefdes[1], data);
        execute_pipeline(tree->right_child, pipefdes[0], fd_out, data);
        close(pipefdes[1]);
        close(pipefdes[0]);
    }
}

void    execute(t_node *tree, t_data *data)
{
    if (!tree->left_child)
    {
        if (tree->redirs != NULL)
            update_fd(tree->redirs, &(data->fd_in), &(data->fd_out), 1);
        if (run_bultins(tree->args, &(data->env_var), &data, data->fd_out) != -1)
            return ;
        execute_pipeline(tree, 0, 1, data);
    }
    else 
        execute_pipeline(tree, 0, 1, data);
    wait_for_last_child(data);
}