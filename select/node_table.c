/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:45:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 15:28:28 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

t_table		*new_table(char **input)
{
	t_table		*node;

	if (!(node = (t_table*)ft_memalloc(sizeof(t_table))))
		return (NULL);
	node->list = build_list(input);
	return (node);
}

void		free_table(t_table *node)
{
	if (node)
	{
		if (node->list)
			free_item_list(node->list);
		free(node);
	}
}

void		print_table(t_select *node)
{
	t_item		*item;

	item = node->table->list->next;
	print_item(item->prev);
	while (item && item != node->table->list)
	{
		ft_putstr("\n");
		print_item(item);
		item = item->next;
	}
}