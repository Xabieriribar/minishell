/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 09:49:03 by rick              #+#    #+#             */
/*   Updated: 2026/02/10 12:56:39 by rick             ###   ########.fr       */
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

char *append_env(t_token *token, int *i, char *result)
{
    char    *env;
    char    *val;
    char    *getval;

    val = token->value;
    (*i)++; // skip the initial $

    // If $ is at the end of the string, just append literal $
    if (val[*i] == '\0')
        return ft_strconcat(result, "$");

    env = NULL;

    // Build the env variable name: letters, digits, underscore
    while (val[*i] && ((val[*i] >= 'A' && val[*i] <= 'Z')
                      || (val[*i] >= 'a' && val[*i] <= 'z')
                      || (val[*i] >= '0' && val[*i] <= '9')
                      || val[*i] == '_'))
    {
        env = append_char(env, val[*i]);
        if (!env)
            return (perror("Err: Malloc"), NULL);
        (*i)++;
    }

    // If no valid variable name, treat it as literal $
    if (!env || env[0] == '\0')
        return ft_strconcat(result, "$");

    // Lookup environment value
    getval = getenv(env);
    if (!getval)
        getval = "";

    // Append value
    result = ft_strconcat(result, getval);
    if (!result)
        return (perror("Err: Malloc"), NULL);

    free(env);
    return result;
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
