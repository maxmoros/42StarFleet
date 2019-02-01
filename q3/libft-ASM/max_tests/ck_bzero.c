/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:28:19 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:28:21 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_bzero(size_t n)
{
	char	*my_s;
	char	*sy_s;

	my_s = calloc(n + 1, 1);
	sy_s = calloc(n + 1, 1);
	memset(my_s, '*', n);
	memset(sy_s, '*', n);
	ft_bzero(my_s, n + 1);
	bzero(sy_s, n + 1);
	if (memcmp(my_s, sy_s, n + 1))
	{
		ft_putstr("failed to zero data with length = \'");
		ft_putnbr((int)n);
		ft_putstr("\'\n");
	}
	assert(!memcmp(my_s, sy_s, n + 1));
}

void			ck_bzero(void)
{
	ft_putstr("ft_bzero: ");
	test_bzero(0);
	test_bzero(1);
	test_bzero(50);
	test_bzero(99);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
