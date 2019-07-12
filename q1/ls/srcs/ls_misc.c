/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:03:49 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/12 14:10:54 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

uint8_t		ft_numlen(int num)
{
	uint8_t		len;

	len = (num ? 0 : 1);
	while (num && ++len)
		num /= 10;
	return (len);
}

static int	cmp_lexi(t_dir *n1, t_dir *n2)
{
	return (ft_strcmp(NAME(n1), NAME(n2)) < 0);
}

static int	cmp_time(t_dir *n1, t_dir *n2)
{
	if (MTIME(n1) == MTIME(n2))
		return (cmp_lexi(n1, n2));
	return ((MTIME(n1) - MTIME(n2)) >= 0);
}

t_dir		*insert_node(t_dir *n1, t_dir *n2)
{
	int		(*cmp)(t_dir*, t_dir*);
	t_dir	*tmp;

	cmp = (FLAG_SET(T_FLAG) ? cmp_time : cmp_lexi);
	if (REV_ON ^ cmp(n2, n1))
	{
		n2->next = n1;
		return (n2);
	}
	tmp = n1;
	while (tmp->next && (REV_ON ^ cmp(tmp->next, n2)))
		tmp = tmp->next;
	if (tmp->next)
		n2->next = tmp->next;
	tmp->next = n2;
	return (n1);
}
