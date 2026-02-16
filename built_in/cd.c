/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:25 by rick              #+#    #+#             */
/*   Updated: 2026/02/16 17:32:14 by rick             ###   ########.fr       */
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

int b_cd(char **args)
{
	char	*str;
	int		errn;

	if (args[1] == NULL)
	{
		str = getenv("HOME");
		if (!str)
			return(printf("cd: HOME env unset\n"), 1);
		errn = chdir(str);
		if (errn == -1)
			return(printf("cd: no such file or directory\n"), 1);
		b_pwd();
		return(0);
	}
	if (args[2] != NULL)
		return (printf("cd: too many arguments\n"), 1);
	errn = chdir(args[1]);
	if (errn == -1)
		return(printf("cd: no such file or directory\n"), 1);
	b_pwd();
	return(0);
}
/* 
int b_cd(char **args, t_env *env) // Pass your env list to the function!
{
    char *current_dir;
    char *old_dir;

    // 1. Save current directory BEFORE moving
    old_dir = get_current_dir_somehow(); // (e.g. get_env_value(env, "PWD"))

    // 2. Move
    if (chdir(args[1]) == -1)
        return (perror("cd"), 1);

    // 3. Get new directory AFTER moving
    current_dir = getcwd(NULL, 0);

    // 4. Update your internal list
    set_env_value(env, "OLDPWD", old_dir); // Edit OLDPWD
    set_env_value(env, "PWD", current_dir); // Edit PWD

    free(current_dir);
    // don't free old_dir if it was a pointer to the list value, careful here!
    return (0);
}

int b_cd(char **args, t_env *env)
{
	char	*old_dir;

	old_dir = 
} */