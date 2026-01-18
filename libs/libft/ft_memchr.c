/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:11:51 by rspinell          #+#    #+#             */
/*   Updated: 2025/10/06 10:07:21 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
The memchr() function scans the initial n bytes of the memory area
pointed to by s for the first instance of c.  Both c and the bytes
of the memory area pointed to by s are interpreted as unsigned
char.

memchr() returns a pointer to the
matching byte or NULL if the character does not occur in the given
memory area.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;

	ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
		n--;
	}
	ptr = NULL;
	return ((void *)0);
}
