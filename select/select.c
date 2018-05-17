/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 10:18:38 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/16 19:32:56 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int		input_loop(t_select *node)
{
	char	buff[3];

	print_table(node);
	while (1)
	{
		read(0, buff, 3);
		if (!ft_strncmp("\x1b\x00\x00", buff, 3))
			free_select(node, 0);
		if (!ft_strncmp("\x1b\x5b", buff, 2))
			navkey(node, buff[2]);
		if (!ft_strncmp("\x20\x00\x00", buff, 3))
			navkey_select(node);
		if (!ft_strncmp("\x7e\x00\x00", buff, 3) ||
			!ft_strncmp("\x7f\x00\x00", buff, 3))
			actkey_remove(node);
		if (!ft_strncmp("\x0a\x00\x00", buff, 3))
			free_select(node, 1);
		print_table(node);
		buff[1] = 0;
		buff[2] = 0;
	}
	return (1);
}

int		ft_select(int count, char **input)
{
	t_select		*node;

	node = init_select(input);
	node->elements = count;
	printf("termtype is %s, buffer is %s\n", node->termtype, node->buffer);
	input_loop(node);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac > 2)
		ft_select(ac - 1, av + 1);
	return (0);
}
