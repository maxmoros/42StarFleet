/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:48:53 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 15:28:20 by mmoros           ###   ########.fr       */
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
	start->state = 0x02;
	tmp = start;
	while (*++input)
		tmp = new_item(tmp, NULL, *input);
	tmp->next = start;
	start->prev = tmp;
	while (tmp != start)
	{
		tmp->prev->next = tmp;
		tmp = tmp->prev;
	}
	return (start);
}

void			remove_item(t_select *node, t_item *item)
{
	if (item == item->next)
		free_select(node, 0);
	if (node->table->list == item)
		node->table->list = item->next;
	item->next->prev = item->prev;
	item->prev->next = item->next;
	free(item);
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

void			print_item(t_item *node)
{
	ft_putstr("\033[0;m");
	if (node->state & 0x01)
		ft_putstr("\033[07m");
	if (node->state & 0x02)
		ft_putstr("\033[04m");
	ft_putstr(node->name);
	ft_putstr("\033[0;m");
}