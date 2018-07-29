/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:39:35 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:06:31 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*output;

	if (!lst && (*f))
		return (NULL);
	if (lst->next)
		output = ft_lstmap(lst->next, (*f));
	ft_lstadd(&output, (*f)(lst));
	return (output);
}
