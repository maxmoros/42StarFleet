/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:33:09 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:33:11 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_strlen(char *str)
{
	int		my_r;
	int		sy_r;

	my_r = strlen(str);
	sy_r = strlen(str);
	if (my_r != sy_r)
	{
		ft_putstr("\x1b[31mKO!\x1b[0m\n");
		ft_putstr("failed at \'");
		ft_putstr(str);
		ft_putstr("\', got \'");
		ft_putnbr(my_r);
		ft_putstr("\'\n");
	}
	assert(my_r == sy_r);
}

void			ck_strlen(void)
{
	ft_putstr("ft_strlen: ");
	test_strlen("");
	test_strlen("this is a test");
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
