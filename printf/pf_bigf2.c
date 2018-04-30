/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_bigf2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 21:31:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 21:39:02 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			count_bigoct(uintmax_t oct)
{
	int		count;

	if (!oct)
		return (1);
	count = 0;
	while (oct)
	{
		count++;
		oct /= 8;
	}
	return (count);
}

static int	dig_bigoct(uintmax_t oct)
{
	int		count;

	if (oct)
	{
		count = 1 + dig_bigoct(oct / 8);
		ft_putchar('0' + oct % 8);
		return (count);
	}
	return (0);
}

int			put_bigoct(uintmax_t oct)
{
	if (!oct)
	{
		ft_putchar('0');
		return (1);
	}
	return (dig_bigoct(oct));
}

int			dig_bighex(uintmax_t hex, char format)
{
	int		count;

	if (hex)
	{
		count = 1 + dig_bighex(hex / 16, format);
		if (!(format & 0xF0))
		{
			if (hex % 16 > 9)
			{
				if (format & 0x1)
					ft_putchar('A' + hex % 16 - 10);
				else
					ft_putchar('a' + hex % 16 - 10);
			}
			else
				ft_putchar('0' + hex % 16);
		}
		return (count);
	}
	return (0);
}

int			put_bighex(uintmax_t hex, t_conv *node, char format)
{
	int		count;

	count = 0;
	if (!hex)
	{
		if (!(format & 0xF0))
			ft_putchar('0');
		while (!(format & 0xF0) && ++count < node->precision)
			ft_putchar('0');
		return (node->precision ? node->precision : 1);
	}
	if (node->flags & 0x1)
	{
		count += 2;
		if (!(format & 0xF0) && format & 0x1)
			write(1, "0X", 2);
		else if (!(format & 0xF0))
			write(1, "0x", 2);
	}
	node->j = dig_bighex(hex, 0xF0);
	if (!(format & 0xF0) && node->precision > node->j)
		zpadding(node->precision - node->j);
	dig_bighex(hex, format);
	node->j = (node->precision > node->j ? node->precision : node->j);
	return (node->j += count);
}
