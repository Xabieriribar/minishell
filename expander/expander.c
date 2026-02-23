/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:49:03 by rick              #+#    #+#             */
/*   Updated: 2026/02/23 17:57:11 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Helper function that will append char by char
* allocating +1 byte and helping to copy one by one.*/
static char	*append_char(char *str, char c)
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

/*
* Helper function to handle the getenv() case, where we
* add to our result the evironment variable value returned
* by the function getenv().*/
static int	append_getenv(char *env, char **result)
{
	char	*getval;
	char	*new_res;

	if (!env || env[0] == '\0')
	{
		new_res = ft_strconcat(*result, "$");
		if (!new_res)
			return (0);
		*result = new_res;
		return (1);
	}
	getval = getenv(env);
	if (!getval)
		getval = "";
	new_res = ft_strconcat(*result, getval);
	if (!new_res)
		return (0);
	*result = new_res;
	return (1);
}

/*
* Main logic to append evironment variables and also
* previous exit status after a dollar sign ($).*/
static char	*append_env(char *value, int *i, char *result)
{
	char	*env;
	char	*val;

	val = value;
	(*i)++;
	if (val[*i] == '\0')
		return (ft_strconcat(result, "$"));
	env = NULL;
	while (val[*i] && valid_chars(val[*i]))
	{
		env = append_char(env, val[*i]);
		if (!env)
			return (perror("Err: Malloc"), NULL);
		(*i)++;
	}
	append_getenv(env, &result);
	if (!result)
		return (perror("Err: Malloc"), NULL);
	return (free(env), result);
}

char	*expand_buff(char *str)
{
	int		i;
	char	*result;
	char	*val;

	i = 0;
	result = NULL;
	val = NULL;
	while (str && str[i] && !is_dollar(str[i]))
		i++;
	if (str[i] == '\0')
		return (str);
	val = str;
	while (val && val[i])
	{
		if (is_dollar(val[i]))
			result = append_env(str, &i, result);
		else
		{
			result = append_char(result, val[i]);
			i++;
		}
		if (!result)
			return (perror("Err: Malloc"), NULL);
	}
	return (free(str), result);
}

char	*expander(t_token *token)
{
	int		i;
	char	*result;
	char	*val;

	if (token->dolar != 1
		|| ((token->value[0] == '$' && token->value[1] == '\0')))
		return (token->value);
	i = 0;
	result = NULL;
	val = token->value;
	while (val && val[i])
	{
		if (is_dollar(val[i]))
			result = append_env(token->value, &i, result);
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
