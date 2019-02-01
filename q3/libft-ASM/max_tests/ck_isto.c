/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_isto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:28:31 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:28:33 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_isto(int c, int (ft_x)(int), int (sysx)(int))
{
	int		my_r;
	int		sy_r;

	my_r = ft_x(c);
	sy_r = sysx(c);
	if (my_r != sy_r)
	{
		ft_putstr("\x1b[31mKO!\x1b[0m\n");
		ft_putstr("failed at \'");
		ft_putchar(c);
		ft_putstr("\', got \'");
		ft_putchar(my_r);
		ft_putstr("\'\n");
	}
	assert(my_r == sy_r);
}

void			ck_isto(int (ft_x)(int), int (sysx)(int), char *func)
{
	int		i;

	ft_putstr(func);
	ft_putstr(": ");
	i = -555;
	while (++i < 555)
		test_isto(i, ft_x, sysx);
	test_isto(EOF, ft_x, sysx);
	test_isto(INT_MIN, ft_x, sysx);
	test_isto(INT_MAX, ft_x, sysx);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
