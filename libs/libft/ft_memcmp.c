/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:11:59 by rspinell          #+#    #+#             */
/*   Updated: 2025/10/06 10:10:15 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
       The memcmp() function compares the first n bytes (each interpreted
       as unsigned char) of the memory areas s1 and s2.

RETURN VALUE

       The memcmp() function returns an integer less than, equal to, or
       greater than zero if the first n bytes of s1 is found,
       respectively, to be less than, to match, or be greater than the
       first n bytes of s2.

       For a nonzero return value, the sign is determined by the sign of
       the difference between the first pair of bytes (interpreted as
       unsigned char) that differ in s1 and s2.

       If n is zero, the return value is zero.

*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
		n--;
	}
	return (0);
}
