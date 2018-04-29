/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convf1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:23:44 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/28 19:04:51 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		do_conv(va_list ap, t_conv *node, char *error)
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

void	*get_length(va_list ap, char length)
{
	void	*data;

	if (length & 0x20 && (data = ft_memalloc(sizeof(char))))
		*(char*)data = (char)va_arg(ap, int);
	else if (length & 0x10 && (data = (void*)ft_memalloc(sizeof(short))))
		*(short*)data = (short)va_arg(ap, int);
	else if (length & 0x8 && (data = (void*)ft_memalloc(sizeof(long))))
		*(long*)data = va_arg(ap, long);
	else if (length & 0x4 && (data = (void*)ft_memalloc(sizeof(long long))))
		*(long long*)data = va_arg(ap, long long);
	else if (length & 0x2 && (data = (void*)ft_memalloc(sizeof(intmax_t))))
		*(intmax_t*)data = va_arg(ap, intmax_t);
	else if (length & 0x1 && (data = (void*)ft_memalloc(sizeof(ptrdiff_t))))
		*(ptrdiff_t*)data = va_arg(ap, ptrdiff_t);
	else
		return (NULL);
	return (data);
}

int		conv_s(va_list ap, t_conv *node)
{
	char	*out;

	out = (node->length ? (char*)get_length(ap, node->length)
						: va_arg(ap, char*));
	ft_putstr(out);
	return (node->j);
}

int		conv_di(va_list ap, t_conv *node)
{
	intmax_t	out;

	out = (node->length ? *(intmax_t*)get_length(ap, node->length)
						: va_arg(ap, int));
	put_intmax_t(out, 1);
	return (node->j);
}

int		conv_o(va_list ap, t_conv *node)
{
	unsigned int	out;

	out = (node->length ? *(unsigned int*)get_length(ap, node->length)
						: va_arg(ap, unsigned int));
	ft_putoct((unsigned int)out);
	return (node->j);
}

int		conv_u(va_list ap, t_conv *node)
{
	uintmax_t	out;

	out = (node->length ? *(uintmax_t*)get_length(ap, node->length)
						: va_arg(ap, unsigned int));
	put_uintmax_t(out, 1);
	return (node->j);
}

int		conv_p(va_list ap, t_conv *node)
{
	void	*out;

	out = (node->length ? (void*)get_length(ap, node->length)
						: va_arg(ap, void*));
	ft_puthex_f((unsigned int)out, 0xA);
	return (node->j);
}

int		conv_x(va_list ap, t_conv *node)
{
	unsigned int	out;
	char			format;

	format = 0x2;
	out = (node->length ? *(unsigned int*)get_length(ap, node->length)
						: (unsigned int)va_arg(ap, unsigned int));
	if (node->flags & 0x1)
		format &= 0x8;
	ft_puthex_f(out, format);
	return (node->j);
}

int		conv_X(va_list ap, t_conv *node)
{
	unsigned int	out;
	char			format;

	format = 0x1;
	out = (node->length ? *(unsigned int*)get_length(ap, node->length)
						: va_arg(ap, unsigned int));
	if (node->flags & 0x1)
		format &= 0x4;
	ft_puthex_f(out, format);
	return (node->j);
}

int		conv_c(va_list ap, t_conv *node)
{
	char	out;

	out = (node->length ? *(char*)get_length(ap, node->length)
						: (char)va_arg(ap, int));
	ft_putchar(out);
	return (node->j);
}
