/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:12:13 by rspinell          #+#    #+#             */
/*   Updated: 2025/09/29 16:27:52 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*cdest;
	unsigned char	*csrc;

	i = 0;
	if (!dest && !src)
		return (NULL);
	cdest = (unsigned char *)dest;
	csrc = (unsigned char *)src;
	if (cdest > csrc)
	{
		while (n > 0)
		{
			n--;
			cdest[n] = csrc[n];
		}
		return (dest);
	}
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}
