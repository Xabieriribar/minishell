/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:25 by rick              #+#    #+#             */
/*   Updated: 2026/02/17 17:05:17 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* STACK OVERFLOW IMPORTANT INFO:
+ chdir will change the current directory of your program, probably a
+ command shell you are trying to implement.

+ Absolute and relative paths such as /, .., subdir pose no
+ problem and can be passed directly to the chdir system call.

- '-' is a special argument for the cd command: cd - means to go back to the previous 
- current directory. To implement this functionality, you need to keep track of the
- last directory cd changed to. Use the getcwd() function for that before calling chdir
- and if successful, keep this previous directory in a global array.

- '~' is another special thing: it should be expanded to the home directory
- (the value of the HOME environment variable) before dispatching to the command handler,
- so one can type cd ~, or just cd to change to the home directory but cd "~" to change
- to a directory named "~". ~ should expand to $(HOME), either as a stand alone string
- or as the initial portion of a path: ~/bin. Note that ~name should expand to the home
- directory of the user name.*/

/*
~ IMPORTANT DATA NEEDED:
+ Previous directory
+ Env variable $HOME */

/*
* Function iterates though the linked list until finding a matching name.
* Returns a pointer to the matching string key or NULL if not found.*/
static char    *get_env_value(t_env *env, char *key)
{
    t_env   *ptr;
    size_t  len;

    ptr = env;
    len = ft_strlen(key);
    while (ptr)
    {
        if (ft_strncmp(key, ptr->key, len) == 0 && ptr->key[len] == '\0')
            return (ptr->value);
        ptr = ptr->next;
    }
    return (NULL);
}

static int update_env(t_env *env, char *key, char *new_val)
{
    t_env   *ptr;
    size_t  len;

    ptr = env;
    len = ft_strlen(key);
    while (ptr)
    {
        if (ft_strncmp(key, ptr->key, len) == 0 && ptr->key[len] == '\0')
        {
            if (ptr->value)
                free(ptr->value);
            ptr->value = ft_strdup(new_val);
            return (0);
        }
        ptr = ptr->next;
    }
// 2. Key not found? Create and Add it.
    // Note: We need a specialized init that doesn't split by '='
    new_node = ft_calloc(1, sizeof(t_env));
    if (!new_node)
        return (1);
    new_node->key = ft_strdup(key);
    if (value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = NULL;
    
    // Add to back of list (using your existing list function)
    lst_add_back_env(&head, new_node);
    return (1);
}

static int  change_dir(t_env *env, char *path)
{
    char    *old_pwd;
    char    *new_pwd;

    old_pwd = get_env_value(env, "PWD");
    if (chdir(path) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        return (1);
    }
    if (old_pwd)
        update_env(env, "OLDPWD", old_pwd);
    new_pwd = getcwd(NULL, 0);
    if (new_pwd)
    {
        update_env(env, "PWD", new_pwd);
        free(new_pwd);
    }
    return (0);
}

int b_cd(t_env *env, char **args)
{
    char    *path;
	int		ret;

    if (!args[1])
    {
        path = get_env_value(env, "HOME");
        if (!path)
            return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
        return (change_dir(env, path));
    }
    if (args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	ret = change_dir(env, args[1]);
	b_pwd();
    return (ret);
}
