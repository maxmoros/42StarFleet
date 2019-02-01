/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:31:46 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:32:41 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_memset(void *s, int c, size_t n)
{
	char	*a;
	char	*b;

	a = strdup((char*)s);
	b = strdup((char*)s);
	ft_memset(a, c, n);
	memset(b, c, n);
	if (strcmp(a, b))
	{
		ft_putstr("\x1b[31mKO!\x1b[0m\n");
		ft_putstr("failed at \'");
		ft_putstr((char*)s);
		ft_putstr("\', got \'");
		ft_putstr(a);
		ft_putstr("\', should be \'");
		ft_putstr(b);
		ft_putstr("\'\n");
	}
	assert(!strcmp(a, b));
}

void			ck_memset(void)
{
	ft_putstr("ft_memset: ");
	test_memset("maxmax", 'a', 3);
	test_memset("this is a test", 'b', 8);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
