/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:15:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 21:36:35 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthexdig(unsigned int hex, char format)
{
	int		count;

	count = 0;
	if (hex)
	{
		count += 1 + ft_puthexdig(hex / 16, format);
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
	}
	return (count);
}

int			ft_puthex_f(unsigned int hex, char format)
{
	int		prefix;

	prefix = 1;
	if (format & 0xC)
	{
		prefix++;
		if (format & 0x1)
		{
			if (!(format & 0xF0))
				ft_putstr("0X");
		}
		else if (!(format & 0xF0))
			ft_putstr("0x");
	}
	if (hex == 0 && !(format & 0xF0))
		ft_putchar('0');
	else
		return (prefix + ft_puthexdig(hex, format));
	return (prefix);
}
