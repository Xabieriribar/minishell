/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:33:50 by zalemu            #+#    #+#             */
/*   Updated: 2026/02/11 12:14:21 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s++;
	}
	if (s && *s == (unsigned char) c)
		return ((char *) s);
	return (NULL);
}

char	*ft_strjoin_gnl(char *prev_line, char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!prev_line && !*buffer)
		return (NULL);
	line = (char *) malloc(ft_strlen_gnl(prev_line) + ft_strlen_gnl(buffer) + 1);
	if (!line)
	{
		free(prev_line);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (prev_line && prev_line[i])
	{
		line[i] = prev_line[i];
		i++;
	}
	while (buffer && buffer[j])
		line[i++] = buffer[j++];
	line[i] = '\0';
	free(prev_line);
	return (line);
}
