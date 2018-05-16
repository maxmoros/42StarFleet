/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 10:18:38 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/15 20:46:49 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "select.h"

int		input_loop(void)
{
	char	buff[3];

	clear_term();
	while (1)
	{
		read(0, buff, 3);
		printf("buff = %d, %d, %d\n", buff[0], buff[1], buff[2]);
		buff[1] = 0;
		buff[2] = 0;
	}
	return (1);
}

int		ft_select(char **input)
{
	t_select		*node;

	node = init_select(input);
	printf("termtype is %s, buffer is %s\n", node->termtype, node->buffer);
	input_loop();
	return (1);
}

int		main(int ac, char **av)
{
	if (ac > 2)
		ft_select(av + 1);
	return (0);
}
