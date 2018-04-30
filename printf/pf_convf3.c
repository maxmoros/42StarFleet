/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convf3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 21:13:23 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 23:13:34 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_p(va_list ap, t_conv *node)
{
	void	*out;

	out = va_arg(ap, void*);
	node->j = ft_puthex_f((unsigned int)out, 0xFA);
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	ft_puthex_f((unsigned int)out, 0xA);
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}

int		conv_x(va_list ap, t_conv *node)
{
	uintmax_t	out;

	if (node->width < 0)
		node->width = va_arg(ap, int);
	if (node->precision < 0)
		node->precision = va_arg(ap, int);
	out = get_ulength(ap, node->length);
	node->j = put_bighex(out, node, 0xF2);
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	node->j = put_bighex(out, node, 0x02);
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}

int		conv_xx(va_list ap, t_conv *node)
{
	uintmax_t	out;

	if (node->width < 0)
		node->width = va_arg(ap, int);
	if (node->precision < 0)
		node->precision = va_arg(ap, int);
	out = get_ulength(ap, node->length);
	node->j = put_bighex(out, node, 0xF1);
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	node->j = put_bighex(out, node, 0x01);
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}

int		conv_c(va_list ap, t_conv *node)
{
	char	out;

	out = (char)va_arg(ap, int);
	node->j = 1;
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	ft_putchar(out);
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}
