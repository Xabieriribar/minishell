/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 11:15:06 by rick              #+#    #+#             */
/*   Updated: 2026/02/12 11:16:03 by rick             ###   ########.fr       */
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
