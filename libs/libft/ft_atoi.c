/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:11:07 by rspinell          #+#    #+#             */
/*   Updated: 2025/10/06 09:58:34 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Converts a string to its int representation

27. skip whitespaces
33. set the sign
40. iterate and set the numbers digit by digit
46. return int
*/

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while ((*nptr >= 9 && *nptr <= 13)
		|| *nptr == 32)
	{
		nptr++;
	}
	if ((*nptr == '+') || (*nptr == '-'))
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (num * sign);
}
