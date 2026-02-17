#include "minishell.h"
void	free_splits(char **strs, int index_allocated)
{
    int index;

    index = 0;
    while (index < index_allocated) 
    {
        free(strs[index]);
        index++;
    }
    free(strs);
}
t_env *return_path(t_env *env_var)
{
    while (env_var)
    {
        if (!ft_strncmp(env_var->key, "PATH", ft_strlen("PATH")))
        {
            return env_var;
        }
        env_var = env_var->next;
    }
    return (NULL);
}
char    **fill_array_with_env_vars(t_env *env_var)
{
    char    **result;
    char    *candidate;
    char    *temp;
    int     index;

    index = 0;
    result = NULL;
    while (env_var)
    {
        temp = ft_strjoin(env_var->key, "=");
        if (!temp)
            return (free_splits(result, index), NULL);
        candidate = ft_strjoin(temp, env_var->value);
        free(temp);
        if (!candidate)
            return (free_splits(result, index), NULL);
        result[index] = candidate;
        env_var = env_var->next;
        index++;
    }
    result[index] = NULL;
    return (result);
}
char    **convert_env_var_to_array(t_env *env_var, int env_var_lstsize)
{
    char    **result;

    if (!env_var)
        return (NULL);
    result = malloc(sizeof(char *) * (env_var_lstsize + 1));
    if (!result)
        return (NULL);
    result = fill_array_with_env_vars(env_var);
    if (!result)
        return (NULL);
    return (result);
}
int ft_env_var_lstsize(t_env *env_var)
{
    int lstsize;

    lstsize = 0;
    while (env_var)
    {
        lstsize++;
        env_var = env_var->next;
    }
    return (lstsize);
}