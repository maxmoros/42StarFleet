/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigf1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 18:08:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 21:36:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_intmax_t(uintmax_t num)
{
	int		count;

	if (!num)
		return (0);
	count = 0;
	count += 1 + print_intmax_t(num / 10);
	ft_putchar('0' + num % 10);
	return (count);
}

static int	count_intmax_t(uintmax_t num)
{
	if (num)
		return (1 + count_intmax_t(num / 10));
	return (0);
}

int			put_intmax_t(intmax_t num, char print)
{
	int		count;

	count = 0;
	if (!num)
	{
		if (print)
			ft_putchar('0');
		return (1);
	}
	else if (num < 0)
	{
		if (print)
			ft_putchar('-');
		num *= -1;
		count++;
	}
	return (count + (print ? print_intmax_t(num) : count_intmax_t(num)));
}

int			put_uintmax_t(uintmax_t num, char print)
{
	int		count;

	count = 0;
	if (!num)
	{
		if (print)
			ft_putchar('0');
		return (1);
	}
	return (print ? print_intmax_t(num) : count_intmax_t(num));
}
