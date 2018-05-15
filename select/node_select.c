/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:27:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/14 21:38:41 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

t_select	*init_select(void)
{
	t_select	*node;

	if (!(node = (t_select*)ft_memalloc(sizeof(t_select))) ||
		!(node->buffer = (char*)ft_memalloc(2048)) ||
		!(node->table = (t_table*)ft_memalloc(sizeof(t_table))))
	{
		free_select(node, 0);
		return (NULL);
	}
}

int			free_select(t_select *node, int out)
{
	t_item	*tmp1;
	t_item	*tmp2;

	if (node)
	{
		if (node->buffer)
			free(node->buffer);
		if (node->table)
		{
			if (node->table->list)
				free_item_list(node->table->list);
			free(node->table);
		}
		free(node);
	}
	return (out);
}
