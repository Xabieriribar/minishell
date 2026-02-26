/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:15:06 by rick              #+#    #+#             */
/*   Updated: 2026/02/26 18:11:56 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	valid_chars(char c)
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
	res = (char *) ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
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

/*
* Function returns a string value matching with thechar *key
* in case of not finding it, returns NULL.*/
char	*get_env_value(t_env *env, char *key)
{
	t_env	*ptr;
	size_t	len;

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
