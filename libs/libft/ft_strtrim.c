/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:31:14 by rick              #+#    #+#             */
/*   Updated: 2025/10/02 19:44:21 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	charcmp(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		s;
	int		e;
	int		i;

	s = 0;
	i = 0;
	e = ft_strlen(s1) - 1;
	while (charcmp(s1[s], set))
		s++;
	if ((ft_strlen(s1) == 0) || (s >= e))
		return (ft_strdup(""));
	while (charcmp(s1[e], set))
		e--;
	dst = (char *) malloc(sizeof(char) * (2 + e - s));
	if (!dst)
		return (NULL);
	while ((s + i) <= e)
	{
		dst[i] = s1[s + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
