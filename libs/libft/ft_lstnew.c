/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rick <rick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:50:55 by rspinell          #+#    #+#             */
/*   Updated: 2025/10/03 22:19:47 by rick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
This function allocates memory for a new element of type t_list,
setting its content to be the content parameter, 
and setting the next variable to NULL.

Then it returns the newly allocated / created element of the list.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*li;

	li = malloc(sizeof(t_list));
	if (!li)
		return (NULL);
	li->content = content;
	li->next = NULL;
	return (li);
}
