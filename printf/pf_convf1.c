/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convf1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:23:44 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 23:15:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			do_conv(va_list ap, t_conv *node, char *error)
{
	write(1, node->prefix, node->i);
	if (node->flags & 0x80)
		ft_putchar('%');
	else if (node->type)
		node->type(ap, node);
	if (node->next)
		do_conv(ap, node->next, error);
	return (1 - *error);
}

intmax_t	get_length(va_list ap, char length)
{
	if (length & 0x20)
		return ((char)va_arg(ap, intmax_t));
	else if (length & 0x10)
		return ((short)va_arg(ap, intmax_t));
	else if (length & 0x8)
		return ((long)va_arg(ap, intmax_t));
	else if (length & 0x4)
		return ((long long)va_arg(ap, intmax_t));
	else if (length & 0x2)
		return (va_arg(ap, intmax_t));
	else if (length & 0x1)
		return ((ptrdiff_t)va_arg(ap, intmax_t));
	return (va_arg(ap, intmax_t));
}

uintmax_t	get_ulength(va_list ap, char length)
{
	if (length & 0x20)
		return ((char)va_arg(ap, uintmax_t));
	else if (length & 0x10)
		return ((short)va_arg(ap, uintmax_t));
	else if (length & 0x8)
		return ((long)va_arg(ap, uintmax_t));
	else if (length & 0x4)
		return ((long long)va_arg(ap, uintmax_t));
	else if (length & 0x2)
		return (va_arg(ap, uintmax_t));
	else if (length & 0x1)
		return ((ptrdiff_t)va_arg(ap, uintmax_t));
	return (va_arg(ap, intmax_t));
}

int			padding(t_conv *node)
{
	int		i;

	i = 0;
	if (node->width - node->j > 0)
	{
		if (node->flags & 0x2 && !(node->flags & 0x8))
			while (i++ < node->width - node->j)
			{
				if (!node->precision || i + node->j < node->precision)
					ft_putchar('0');
				else
					ft_putchar(' ');
			}
		else
			while (i++ < node->width - node->j)
				ft_putchar(' ');
		i--;
	}
	return (i);
}

int			zpadding(int i)
{
	int	j;

	j = i;
	if (i > 0)
		while (i--)
			ft_putchar('0');
	return (j);
}
