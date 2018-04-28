/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_f.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:15:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/27 18:56:07 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthexdig(unsigned int hex, char format)
{
	if (hex)
	{
		return (1 + ft_puthexdig(hex / 16, format));
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
	return (0);
}

int			ft_puthex_f(unsigned int hex, char format)
{
	int		prefix;

	prefix = 0;
	if (format & 0xC)
	{
		prefix = 2;
		if (format & 0x1)
			ft_putstr("0X");
		else
			ft_putstr("0x");
	}
	if (hex == 0)
		ft_putchar('0');
	else
		return (prefix + ft_puthexdig(hex, format));
	return (prefix + 1);
}
