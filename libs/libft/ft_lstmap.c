/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rspinell <rspinell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:57:31 by rspinell          #+#    #+#             */
/*   Updated: 2025/10/06 12:04:58 by rspinell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Iterates through the list ’lst’, applies the
function ’f’ to each node’s content, and creates
a new list resulting of the successive applications
of the function ’f’.  The ’del’ function is used to
delete the content of a node if needed.

This functions copies a list, setting the content
of the new elements to f(oldelement.content).

Return the first element of new list.

WHILE LOOP:
45. iterate until lst == NULL
47. create new temp with ft_lstnew node
    and set the content to f(lst->content)
48. controll malloc, otherwise, clear new list
	and return NULL
54. add temp to last element
55. lst = lst->next (advance)
56. return new
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst->next;
	}
	return (new);
}
