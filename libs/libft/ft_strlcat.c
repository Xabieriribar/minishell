/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:26:24 by rspinell          #+#    #+#             */
/*   Updated: 2025/09/29 16:26:30 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* 
Measure dlen = strlen(dst) once.

If dlen >= dsize, you can’t append anything, and return dsize + strlen(src).

Otherwise, you have dsize - dlen - 1 space for copying. 
*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	unsigned char	*srcs;
	unsigned char	*dest;
	size_t			dlen;
	size_t			space;

	if (!src && !dst)
		return (0);
	if (dsize == 0)
		return (ft_strlen(src));
	dlen = (size_t)ft_strlen(dst);
	if (dlen >= dsize)
		return (dsize + ft_strlen(src));
	srcs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (*dest)
		dest++;
	space = dsize - dlen - 1;
	while (space-- > 0 && *srcs)
	{
		*dest = *srcs;
		dest++;
		srcs++;
	}
	*dest = '\0';
	return (ft_strlen(src) + dlen);
}
