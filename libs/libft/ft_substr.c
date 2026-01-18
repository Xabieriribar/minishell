/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 23:26:02 by rick              #+#    #+#             */
/*   Updated: 2025/10/06 10:51:12 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_substr returns a substring of the string s passed as parameter.

str: the string to take a substring from
start: starting position (index) of the extracted string
length: length of string to return

32. Check for empty string
35. Check index "out of bounds"
38. Check for good mem alloc in case len
	is bigger than the actual amount of char to copy.
41. Allocate memory
46. Start at s + start
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	ptr = (char *) s + start;
	i = 0;
	while (i < len)
	{
		*dst = *ptr;
		dst++;
		ptr++;
		i++;
	}
	*dst = '\0';
	return (dst - len);
}
