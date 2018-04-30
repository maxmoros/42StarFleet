/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convf2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 21:12:21 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 22:56:47 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			conv_s(va_list ap, t_conv *node)
{
	char	*out;

	if (node->width < 0)
		node->width = va_arg(ap, int);
	if (node->precision < 0)
		node->precision = va_arg(ap, int);
	out = va_arg(ap, char*);
	if (node->precision > 0 && (int)ft_strlen(out) > node->precision)
		node->j = node->precision;
	else
		node->j = ft_strlen(out);
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	write(1, out, node->j);
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}

int			conv_di(va_list ap, t_conv *node)
{
	intmax_t	out;

	if (node->width < 0)
		node->width = va_arg(ap, int);
	if (node->precision < 0)
		node->precision = va_arg(ap, int);
	out = get_length(ap, node->length);
	node->j = put_intmax_t(out, 0);
	if (node->j < node->precision)
		node->j = node->precision;
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	node->j = put_intmax_t(out, 0);
	zpadding(node->precision - node->j);
	put_intmax_t(out, 1);
	if (node->j < node->precision)
		node->j = node->precision;
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}

static int	conv_o2(t_conv *node, unsigned int out)
{
	if (node->j < node->precision)
		zpadding(node->precision - node->j);
	else if (node->flags & 0x1)
		ft_putchar('0');
	put_bigoct((unsigned int)out);
	if (node->j < node->precision)
		node->j = node->precision;
	else if (node->flags & 0x1)
		node->j++;
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}

int			conv_o(va_list ap, t_conv *node)
{
	uintmax_t	out;

	if (node->width < 0)
		node->width = va_arg(ap, int);
	if (node->precision < 0)
		node->precision = va_arg(ap, int);
	out = get_ulength(ap, node->length);
	node->j = count_bigoct(out);
	if (node->j < node->precision)
		node->j = node->precision;
	else if (node->flags & 0x1)
		node->j++;
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	node->j = count_bigoct(out);
	return (conv_o2(node, out));
}

int			conv_u(va_list ap, t_conv *node)
{
	uintmax_t	out;

	if (node->width < 0)
		node->width = va_arg(ap, int);
	if (node->precision < 0)
		node->precision = va_arg(ap, int);
	out = get_ulength(ap, node->length);
	node->j = put_uintmax_t(out, 0);
	if (node->j < node->precision)
		node->j = node->precision;
	if (!(node->flags & 0x8))
		node->padding = padding(node);
	node->j = put_uintmax_t(out, 0);
	zpadding(node->precision - node->j);
	put_uintmax_t(out, 1);
	if (node->j < node->precision)
		node->j = node->precision;
	if (node->flags & 0x8)
		node->padding = padding(node);
	return (node->j += node->padding);
}
