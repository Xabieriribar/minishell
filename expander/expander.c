/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:49:03 by rick              #+#    #+#             */
/*   Updated: 2026/02/25 10:45:44 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* Helper function to handle the get environment case, where we
* add to our result the evironment variable value returned
* by the function get_env_value()
- get_env_value() is our own getenv(), that gets the value but
- from the list of environment variables.*/
static int	append_getenv(char *env, char **result, t_data *data)
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
	getval = get_env_value(data->env_var, env);
	if (!getval)
		getval = "";
	new_res = ft_strconcat(*result, getval);
	if (!new_res)
		return (0);
	*result = new_res;
	return (1);
}

/*
* Helper function to handle the $?, in this case we dont get the data
* from the list of environment variables, but instead, we get it
* from the data->exit_code.*/
static char	*handle_exit(char *result, int *i, t_data *data, char **env)
{
	char	*tmp;

	*env = ft_itoa(data->exit_status);
	if (!*env)
		return (perror("Err: Malloc"), NULL);
	tmp = ft_strconcat(result, *env);
	if (!tmp)
		return (perror("Err: Malloc"), NULL);
	(*i)++;
	return (tmp);
}

/*
* Function to append to our result the environment variables, this
* will modify the result, adding the environment variables to the string
* and errasing the "KEY", if not found, it wont keep the "KEY"*/
static char	*append_env(char *value, int *i, char *result, t_data *data)
{
	char	*env;

	(*i)++;
	if (value[*i] == '\0')
		return (ft_strconcat(result, "$"));
	env = NULL;
	if (value[*i] == '?')
		result = handle_exit(result, i, data, &env);
	else
	{
		while (value[*i] && valid_chars(value[*i]))
		{
			env = append_char(env, value[*i]);
			if (!env)
				return (perror("Err: Malloc"), NULL);
			(*i)++;
		}
		append_getenv(env, &result, data);
		if (!result)
			return (perror("Err: Malloc"), NULL);
	}
	return (free(env), result);
}

/*
* Expander used when appending a string to a token.*/
char	*expand_buff(char *str, t_data *data)
{
	int		i;
	char	*result;
	char	*val;

	i = 0;
	result = NULL;
	while (str && str[i] && !is_dollar(str[i]))
		i++;
	if (str[i] == '\0')
		return (str);
	val = str;
	while (val && val[i])
	{
		if (is_dollar(val[i]))
			result = append_env(str, &i, result, data);
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

/*
* Expander used when creating a token.*/
char	*expander(t_token *token, t_data *data)
{
	int		i;
	char	*result;
	char	*val;

	if (token->dolar != 1
		|| (token->value[0] == '$' && token->value[1] == '\0'))
		return (token->value);
	i = 0;
	result = NULL;
	val = token->value;
	while (val && val[i])
	{
		if (is_dollar(val[i]))
			result = append_env(token->value, &i, result, data);
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
