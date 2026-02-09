/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:28:50 by rick              #+#    #+#             */
/*   Updated: 2026/02/09 16:57:54 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*dst;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *) malloc(sizeof(char) * len);
	if (!dst)
		return (NULL);
	ptr = (char *) s1;
	while (*ptr)
	{
		*dst = *ptr;
		dst++;
		ptr++;
	}
	ptr = (char *) s2;
	while (*ptr)
	{
		*dst = *ptr;
		dst++;
		ptr++;
	}
	*dst = '\0';
	return ((dst - (len - 1)));
}
