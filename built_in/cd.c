/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:47:25 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 19:13:48 by rick             ###   ########.fr       */
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
* This function compares the first argument inside the array
* of strings found in the node CMD, and executes the respective
* builtin command.
+ If no command is run returns 0
+ If command found and execution:success returns 1
+ If command found and execution:error, returns -1
+ Errors for each command are handled internally.*/
/* int	run_bultins(char **args)
{
	if (!args || !*args)
		return (0);
	if (!ft_strncmp(args[0], "cd", 2));
		return(b_cd(args));
	if (!ft_strncmp(args[0], "echo", 4));
		return(b_echo(args));
	if (!ft_strncmp(args[0], "env", 3));
		return(b_env(args));
	if (!ft_strncmp(args[0], "exit", 4));
		return(b_exit(args));
	if (!ft_strncmp(args[0], "export", 6));
		return(b_export(args));
	if (!ft_strncmp(args[0], "pwd", 3));
		return(b_pwd(args));
	if (!ft_strncmp(args[0], "unset", 5));
		return(b_unset(args));
	return(0);
} */
/* 
int b_cd(char **args)
{
	char	*str;
	int		errn;

	if (args[2] != NULL)
		return (printf("cd: too many arguments\n"), -1);
	if (args[1] == NULL)
	{
		str = getenv("HOME");
		if (!str)
			return(printf("cd: HOME env unset\n"), -1);
		errn = chdir(str);
		if (errn == -1)
			return(printf("cd: no such file or directory\n"), -1);
		return(1);
	}
	errn = chdir(args[1]);
	if (errn == -1)
		return(printf("cd: no such file or directory\n"), -1);
	return(1);
} */
