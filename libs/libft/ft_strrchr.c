/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:12:47 by rspinell          #+#    #+#             */
/*   Updated: 2025/10/06 10:24:57 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (*ptr)
	{
		ptr++;
		i++;
	}
	if (*ptr == '\0' && (unsigned char) c == '\0')
		return (ptr);
	while (i > 0)
	{
		ptr--;
		if (*ptr == (unsigned char) c)
			return (ptr);
		i--;
	}
	ptr = NULL;
	return (ptr);
}
