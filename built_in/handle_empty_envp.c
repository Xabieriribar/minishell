/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_empty_envp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:05:46 by rick              #+#    #+#             */
/*   Updated: 2026/03/04 13:17:15 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*init_pwd(void)
{
	t_env	*pwd;

	pwd = ft_calloc(1, sizeof(t_env));
	if (!pwd)
		return (perror("Malloc"), NULL);
	pwd->key = ft_strdup("PWD");
	if (!pwd->key)
		return (free(pwd), perror("Malloc"), NULL);
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		return (free(pwd->key), free(pwd), perror("Malloc"), NULL);
	pwd->next = NULL;
	pwd->temp = false;
	return (pwd);
}

static t_env	*init_shlvl(void)
{
	t_env	*shlvl;

	shlvl = ft_calloc(1, sizeof(t_env));
	if (!shlvl)
		return (perror("Malloc"), NULL);
	shlvl->key = ft_strdup("SHLVL");
	if (!shlvl->key)
		return (free(shlvl), perror("Malloc"), NULL);
	shlvl->value = ft_strdup("1");
	if (!shlvl->value)
		return (free(shlvl->key), free(shlvl), perror("Malloc"), NULL);
	shlvl->next = NULL;
	shlvl->temp = false;
	return (shlvl);
}

/*
* Inits the environment variable linked list in case we recieve
* an empty array of environment variables.*/
t_env	*init_env_list_default(void)
{
	t_env	*pwd;
	t_env	*shlvl;

	pwd = init_pwd();
	if (!pwd)
		return (perror("Malloc"), NULL);
	shlvl = init_shlvl();
	if (!shlvl)
	{
		free_env_vars(&pwd);
		return (perror("Malloc"), NULL);
	}
	pwd->next = shlvl;
	return (pwd);
}
