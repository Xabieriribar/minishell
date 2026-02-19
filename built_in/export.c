/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:48:07 by rick              #+#    #+#             */
/*   Updated: 2026/02/19 18:44:11 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** =========================================================================
** TODO: b_export
** =========================================================================
** [ ] Case 1 (No args): Create a sorted array/list of the environment, 
** and print them in ASCII order.
** - Print `declare -x KEY="VALUE"` if value exists.
** - Print `declare -x KEY` if value is NULL.
** [ ] Case 2 (With args): Loop through all provided arguments (arr[1]...).
** [ ] For each arg, isolate the key (everything before the first '=').
** [ ] Validate the key using `is_valid_identifier`.
** [ ] If invalid: Print "not a valid identifier", set exit status to 1, 
** but CONTINUE the loop to process the next arguments.
** [ ] If valid (No '='): Add to env list with value NULL (if not present).
** [ ] If valid (Has '='): Add new node OR update existing node's value.
** [ ] Memory check: Ensure split strings, old values, and nodes are freed 
** properly to prevent leaks.
*/

/*
* Checks if a string is a valid Bash identifier.*/
/* static bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || str[0] == '=')
		return (false);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (false);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
} */

/*
* Function to sort and print the environment variables
* list.
+ Used for case where export has no arguments.*/
static void	sort_and_print_export(t_env *env, int out_nmb)
{
	t_env	**arr;
	t_env	*temp;
	int		size;
	int		i;

	size = env_list_size(env);
	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return ;
	i = 0;
	temp = env;
	while (temp)
	{
		arr[i++] = temp;
		temp = temp->next;
	}
	sort_env_arr(arr, size);
	print_arr(arr, size, out_nmb);
	free(arr);
}

int	b_export(char **arr, t_env **env, int out_nmb)
{
	if (!arr[1])
		return (sort_and_print_export(*env, out_nmb), 0);
	return (0);
}
