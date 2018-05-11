/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:38:15 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 19:02:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_io	*new_io(void)
{
	t_io	*node;

	if (!(node = (t_io*)ft_memalloc(sizeof(t_io))))
		return (NULL);
	node->a = 0;
	node->s = 0;
	node->d = 0;
	node->w = 0;
	node->space = 0;
	node->esc = 0;
	return (node);
}

void	free_io(t_io *io)
{
	if (io)
		free(io);
}