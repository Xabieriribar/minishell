/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:19:56 by rspinell          #+#    #+#             */
/*   Updated: 2025/09/29 16:26:39 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*srcs;
	size_t	i;

	srcs = (char *)src;
	i = 0;
	if (size < 1)
		return (ft_strlen(src));
	while (i < size - 1 && *srcs)
	{
		*dst = *srcs;
		i++;
		srcs++;
		dst++;
	}
	*dst = '\0';
	return (ft_strlen(src));
}
