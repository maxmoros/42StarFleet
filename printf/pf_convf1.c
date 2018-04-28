/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convf1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:23:44 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/27 19:24:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		do_conv(va_list ap, t_conv *node, char *error)
{
	write(1, node->prefix, node->i);
	if (node->type)
		node->type(ap, node);
	if (node->next)
		do_conv(ap, node->next, error);
	return (1 - *error);
}

int		percent(va_list ap, t_conv *node)
{
	int		out;

	out = va_arg(ap, int);
	return (node->width);
}

int		conv_s(va_list ap, t_conv *node)
{
	char	*out;

	out = va_arg(ap, char *);
	ft_putstr(out);
	return (node->width);
}

int		conv_di(va_list ap, t_conv *node)
{
	int		out;

	out = va_arg(ap, int);
	ft_putnbr(out);
	return (node->width);
}

int		conv_o(va_list ap, t_conv *node)
{
	void	*out;

	out = va_arg(ap, void*);
	ft_puthex((unsigned int)out);
	return (node->width);
}

int		conv_u(va_list ap, t_conv *node)
{
	unsigned int	out;

	out = va_arg(ap, unsigned int);
	ft_putunbr(out);
	return (node->width);
}

int		conv_p(va_list ap, t_conv *node)
{
	void	*out;

	out = va_arg(ap, void*);
	ft_puthex((unsigned int)out); // add ft_putoct to libft
	return (node->width);
}

int		conv_x(va_list ap, t_conv *node)
{
	unsigned int	out;
	char			format;

	format = 0x2;
	out = va_arg(ap, unsigned int);
	if (node->flags & 0x1)
		format &= 0x8;
	ft_puthex_f(out, format);
	return (node->width);
}

int		conv_X(va_list ap, t_conv *node)
{
	unsigned int	out;
	char			format;

	format = 0x1;
	out = va_arg(ap, unsigned int);
	if (node->flags & 0x1)
		format &= 0x4;
	ft_puthex_f(out, format);
	return (node->width);
}

int		conv_c(va_list ap, t_conv *node)
{
	char	out;

	out = (char)va_arg(ap, int);
	ft_putchar(out);
	return (node->width);
}
