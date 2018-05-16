/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 18:45:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/15 19:59:39 by mmoros           ###   ########.fr       */
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
