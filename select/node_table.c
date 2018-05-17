/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:45:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 20:47:35 by mmoros           ###   ########.fr       */
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

void		set_table(t_select *node)
{
	init_termdata(node->buffer, node->termtype);
	node->height = tgetnum("li");
	node->width = tgetnum("co");
	if (node->elements > node->width / 12)
	{
		node->table->rows = 1 + node->elements / (node->width / 12);
		node->table->cols = node->width / 12;
	}
	else
	{
		node->table->rows = 1;
		node->table->cols = node->elements;
	}
}

void		print_table(t_select *node)
{
	t_item		*item;
	int			row;
	int			col;

	clear_term();
	set_table(node);
	item = node->table->list->next;
	print_item(item->prev);
	col = 0;
	row = 0;
	while (item != node->table->list)
	{
		while (++row < node->table->rows && item != node->table->list)
		{
			ft_putstr(tgoto(tgetstr("cm", NULL), col * 12, row));
			print_item(item);
			item = item->next;
		}
		row = -1;
		col++;
	}
}
