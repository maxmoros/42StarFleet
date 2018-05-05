/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:40:59 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/04 19:50:16 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_dir	*new_dir(struct dirent *data, t_dir *up, t_dir *in, t_dir *next)
{
	t_dir	*node;

	if (!(node = (t_dir*)ft_memalloc(sizeof(t_dir))))
		return (NULL);
	node->data = data;
	node->up = up;
	node->in = in;
	node->next = next;
	return (node);
}

t_dir	*get_nodes(DIR *dir, char flags)
{
	t_dir	*root;

	if (flags & )
}