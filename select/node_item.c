/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:48:53 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/15 20:46:45 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

static t_item	*new_item(t_item *prev, t_item *next, char *item)
{
	t_item		*node;

	if (!(node = (t_item*)ft_memalloc(sizeof(t_item))))
		return (NULL);
	node->name = ft_strdup(item);
	node->prev = prev;
	node->next = next;
	return (node);
}

t_item			*build_list(char **input)
{
	t_item	*start;
	t_item	*tmp;

	start = new_item(NULL, NULL, *input);
	tmp = start;
	while (*++input)
		tmp = new_item(tmp, NULL, *input);
	tmp->next = start;
	while (tmp != start)
	{
		tmp->prev->next = tmp;
		tmp = tmp->prev;
	}
	return (start);
}

void			free_item_list(t_item *node)
{
	t_item	*tmp;

	if (node)
	{
		if (node->next)
		{
			tmp = node->next;
			while (tmp != node)
			{
				tmp = tmp->next;
				free(tmp->prev);
			}
		}
		free(node);
	}
}
