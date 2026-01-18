/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:34:25 by rspinell          #+#    #+#             */
/*   Updated: 2025/11/24 09:58:15 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	* Returns the length of a string */
int	ft_strlen_gnl(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

/*
	* free() stash and set to NULL*/
void	free_stash(char **stash)
{
	free(*stash);
	*stash = NULL;
}

/*
	* BOOL. Function to check if the string
	* contains a new line char ('\n'). */
int	contains_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
	* Allocates memory, filling bytes with 0s */
void	*ft_calloc_gnl(int nmemb, int size)
{
	unsigned char	*ptr;
	int				i;

	i = 0;
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
		ptr[i++] = '\0';
	return (ptr);
}

/*
	* str_realloc() allocates in memory a new string, coping each byte of str
	* into the new string + BUFFER_SIZE '\0' bytes.
	* RETURN: frees the old string and returns the new one. */
char	*str_realloc(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc_gnl(sizeof(char), (ft_strlen_gnl(str) + 1 + 1));
	if (new == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	return (new);
}
