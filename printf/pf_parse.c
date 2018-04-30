/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:37:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 23:08:10 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_flags(char **str, t_conv *node, int *i)
{
	while (**str == '-' || **str == '+' || **str == '0' || **str == '#')
	{
		if (**str == '-' && (*str)++ && ++*i)
			node->flags |= 0x8;
		if (**str == '+' && (*str)++ && ++*i)
			node->flags |= 0x4;
		if (**str == '0' && (*str)++ && ++*i)
			node->flags |= 0x2;
		if (**str == '#' && (*str)++ && ++*i)
			node->flags |= 0x1;
	}
	return (1);
}

int		parse_wp(char **str, t_conv *node, int *i)
{
	if ((ft_isdigit(**str) || **str == '*') && ++*i)
	{
		if (ft_isint(*str) && (node->width = ft_atoi(*str)) > 0)
			while (ft_isdigit(*++*str))
				(*i)++;
		else if (**str == '*' && (*str)++)
			node->width = -1;
		else
			return (0);
	}
	if (**str == '.' && (*str)++ && (*i += 2))
	{
		if (ft_isint(*str) && (node->precision = ft_atoi(*str)) > 0)
			while (ft_isdigit(*++*str))
				(*i)++;
		else if (**str == '*' && (*str)++)
			node->precision = -1;
		else
			return (0);
	}
	return (1);
}

int		parse_len(char **str, t_conv *node, int *i)
{
	if (!ft_strncmp(*str, "hh", 2) && (*i += 2) && (*str += 2))
		node->length = 0x20;
	else if (!ft_strncmp(*str, "h", 1) && ++*i && (*str)++)
		node->length = 0x10;
	else if (!ft_strncmp(*str, "l", 1) && ++*i && (*str)++)
		node->length = 0x08;
	else if (!ft_strncmp(*str, "ll", 2) && (*i += 2) && (*str += 2))
		node->length = 0x04;
	else if (!ft_strncmp(*str, "j", 1) && ++*i && (*str)++)
		node->length = 0x02;
	else if (!ft_strncmp(*str, "z", 1) && ++*i && (*str)++)
		node->length = 0x01;
	return (1);
}

int		parse_type(char **str, t_conv *node, int *i)
{
	if ((**str == 'S' || **str == 'D' || **str == 'O' || **str == 'U' ||
			**str == 'C') && (node->length & 0xF7 || !(node->length = 0x08)))
		return (0);
	if ((**str == 's' || **str == 'S') && ++*i && (*str)++)
		node->type = conv_s;
	else if ((**str == 'd' || **str == 'D' || **str == 'i') && ++*i && (*str)++)
		node->type = conv_di;
	else if ((**str == 'o' || **str == 'O') && ++*i && (*str)++)
		node->type = conv_o;
	else if ((**str == 'u' || **str == 'U') && ++*i && (*str)++)
		node->type = conv_u;
	else if (**str == 'p' && ++*i && (*str)++)
		node->type = conv_p;
	else if (**str == 'x' && ++*i && (*str)++)
		node->type = conv_x;
	else if (**str == 'X' && ++*i && (*str)++)
		node->type = conv_xx;
	else if (**str == 'c' && ++*i && (*str)++)
		node->type = conv_c;
	else
		return (0);
	return (*i);
}

int		parse_conv(char *str, t_conv *node, int *i)
{
	*i = 1;
	if (*++str == '%')
	{
		node->flags = 0x80;
		node->j = 1;
		return (2);
	}
	if (!parse_flags(&str, node, i) || !parse_wp(&str, node, i) ||
			!parse_len(&str, node, i) || !parse_type(&str, node, i))
		return (0);
	return (*i);
}
