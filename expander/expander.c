/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:49:03 by rick              #+#    #+#             */
/*   Updated: 2026/02/09 17:37:59 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strconcat(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	return (free(s1), res);
}

char	*append_env(t_token *token, int *i, char *result)
{
	char	*env;
	char	*val;
	char	*getval;

	env = NULL;
	val = token->value;
	(*i)++;
	while (val[*i] && !is_dollar(val[*i]) && !is_space(val[*i]))
	{
		env = append_char(env, val[*i]);
		if (!env)
			return (perror("Err: Malloc"), NULL);
		(*i)++;
	}
	getval = getenv(env);
	if (getval == NULL)
		getval = "";
	if (!env || env[0] == '\0')
		result = ft_strconcat(result, "$");
	else
		result = ft_strconcat(result, getval);
	if (!result)
		return (perror("Err: Malloc"), NULL);
	return (free(env), result);
}

char	*append_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		new = ft_calloc(sizeof(char), 2);
	else
		new = ft_calloc(sizeof(char), ft_strlen(str) + 2);
	if (!new)
	{
		if (str)
			free(str);
		return (perror("Err: Malloc"), NULL);
	}
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	if (str)
		free(str);
	return (new);
}

char	*expander(t_token *token)
{
	int		i;
	char	*result;
	char	*val;

	if (token->dolar != 1)
		return (token->value);
	i = 0;
	result = NULL;
	val = token->value;
	while (val && val[i])
	{
		if (is_dollar(val[i]))
			result = append_env(token, &i, result);
		else
		{
			result = append_char(result, val[i]);
			i++;
		}
		if (!result)
			return (perror("Err: Malloc"), NULL);
	}
	return (free(token->value), result);
}
