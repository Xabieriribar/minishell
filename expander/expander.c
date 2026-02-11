/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:49:03 by rick              #+#    #+#             */
/*   Updated: 2026/02/11 17:25:48 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	valid_chars(char c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (true);
	return (false);
}

/*
* Concatenates 2 strings, allocating memory for the returning string and freeing
* ONLY THE FIRST ONE, SECOND STRING CAN BE A CONSTANT.*/
char	*ft_strconcat(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2 && !s1)
		return (NULL);
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

/*
* Helper function to handle the "$?" case, where we
* need to access to the previous exit status, stored in
* our global variable g_status.
- (getenv() doesn´t return this.)*/
int	append_status(int *i, char *value, char **result)
{
    char *status_str;

    if (value[*i] != '?')
        return (0);
    
    (*i)++;
    status_str = ft_itoa(g_status);
    *result = ft_strconcat(*result, status_str);
    free(status_str);
    return (1);
}

/*
* Helper function to handle the getenv() case, where we
* add to our result the evironment variable value returned
* by the function getenv().*/
int append_getenv(char *env, char **result)
{
    char    *getval;
    char    *new_res;

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
char *append_env(t_token *token, int *i, char *result)
{
    char    *env;
    char    *val;

    val = token->value;
    (*i)++;
    if (val[*i] == '\0')
        return (ft_strconcat(result, "$"));
    if (append_status(i, val, &result))
        return (result);
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

/*
* Helper function that will append char by char
* allocating +1 byte and helping to copy one by one.*/
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

	if (token->dolar != 1 
		|| ((token->value[0] == '$' && token->value[1] == '\0')))
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
