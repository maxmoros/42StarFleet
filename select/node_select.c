/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 21:27:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/15 20:46:43 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int		set_term(struct termios *orig, struct termios *new)
{
	if (tcgetattr(0, orig) == -1 || tcgetattr(0, new) == -1)
		return (0);
	new->c_lflag &= ~(ICANON);
	new->c_lflag &= ~(ECHO);
	new->c_cc[VMIN] &= 1;
	new->c_cc[VTIME] &= 0;
	if (tcsetattr(0, TCSADRAIN, new) == -1)
		return (0);
	return (1);
}

int		init_termdata(char *buffer, char *termtype)
{
	if (tgetent(buffer, termtype) < 1)
	{
		free(buffer);
		return (0);
	}
	return (1);
}

t_select	*init_select(char **input)
{
	t_select	*node;

	if (!(node = (t_select*)ft_memalloc(sizeof(t_select))) ||
		!(node->buffer = (char*)ft_memalloc(2048)) ||
		!(node->table = new_table(input)) ||
		!(set_term(&node->orig, &node->term)) ||
		!(init_termdata(node->buffer, (node->termtype = getenv("TERM")))))
	{
		free_select(node, 0);
		return (NULL);
	}
	return (node);
}

int			free_select(t_select *node, int out)
{
	if (node)
	{
		if (node->buffer)
			free(node->buffer);
		if (node->table)
			free_table(node->table);
		free(node);
	}
	return (out);
}