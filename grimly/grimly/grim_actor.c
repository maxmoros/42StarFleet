/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_actor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:09:47 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/13 08:41:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "grimly.h"

t_actor		*grim_actor(t_actor *next, int x, int y)
{
	t_actor		*node;

	if (!(node = (t_actor*)ft_memalloc(sizeof(t_actor))))
		return (NULL);
	node->x = x;
	node->y = y;
	node->next = next;
	return (node);
}

void		free_actors(t_actor *node)
{
	t_actor		*tmp;

	tmp = node;
	node = node->next;
	tmp->next = NULL;
	while (node)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
}

int			grim_del(t_actor **node)
{
	t_actor		*tmp;

	if ((*node)->next == (*node))
	{
		free(*node);
		return (-1);
	}
	else
	{
		tmp = (*node)->next;
		(*node)->x = tmp->x;
		(*node)->y = tmp->y;
		(*node)->next = tmp->next;
		free(tmp);
	}
	return (0);
}
