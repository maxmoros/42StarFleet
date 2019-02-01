/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:24:54 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:38:18 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static int g_i;

void	ck_abs(void)
{
	ft_putstr("ft_abs: ");
	g_i = -100;
	while (++g_i < 100)
		assert(abs(g_i) == ft_abs(g_i));
	assert(abs(INT_MIN) == ft_abs(INT_MIN));
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}

void	ck_islower(void)
{
	ft_putstr("ft_islower: ");
	g_i = -1;
	while (++g_i < 'a')
		assert(!ft_islower(g_i));
	while (++g_i <= 'z')
		assert(ft_islower(g_i));
	while (++g_i < 256)
		assert(!ft_islower(g_i));
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}

void	ck_isspace(void)
{
	ft_putstr("ft_isspace: ");
	g_i = -1;
	while (++g_i < 0x09)
		assert(!ft_isspace(g_i));
	while (++g_i < 0x0E)
		assert(ft_isspace(g_i));
	while (++g_i < 0x20)
		assert(!ft_isspace(g_i));
	assert(ft_isspace(0x09));
	while (++g_i < 0xFF)
		assert(!ft_isspace(g_i));
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}

void	ck_isupper(void)
{
	ft_putstr("ft_isupper: ");
	g_i = -1;
	while (++g_i < 'A')
		assert(!ft_isupper(g_i));
	while (++g_i <= 'Z')
		assert(ft_isupper(g_i));
	while (++g_i < 256)
		assert(!ft_isupper(g_i));
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}

void	ck_math_swap(void)
{
	int		x[2];
	int		y[2];
	int		*a;
	int		*b;

	ft_putstr("ft_math_swap: ");
	x[0] = 42;
	x[1] = 42;
	y[0] = -42;
	y[1] = -42;
	a = &x[0];
	b = &y[0];
	ft_math_swap(a, b);
	assert(x[0] != y[0]);
	assert(x[0] == y[1]);
	assert(x[1] == y[0]);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
