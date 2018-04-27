/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:37:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/26 13:58:28 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_flags(char **str, t_conv *node, int *i)
{
	if (**str == '-' || **str == '+' || **str == '0' || **str == '#')
	{
		if (**str == '-' && (*str)++ && ++*i)//IS ORDER SPECIFIC? PAIR COMBO ONES
			node->flags += 0x8;
		if (**str == '+' && (*str)++ && ++*i)
			node->flags += 0x4;
		if (**str == '0' && (*str)++ && ++*i)
			node->flags += 0x2;
		if (**str == '#' && (*str)++ && ++*i)
			node->flags += 0x1;
	}
}

int		parse_wp(char **str, t_conv *node, int *i)
{
	if (ft_isdigit(**str) && ++*i)
	{
		if (ft_isint(*str) && (node->width = ft_atoi(*str)))
			while (ft_isdigit(*++*str))
				(*i)++;
		else
			return (0);
	}
	if (**str == '.' && (*str)++ && (*i += 2))
	{
		if (ft_isint(*str) && (node->precision = ft_atoi(*str)))
			while (ft_isdigit(*++*str))
				(*i)++;
		else
			return (0);
	}
	return (1);
}

void	parse_len(char **str, t_conv *node, int *i)
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
}

int		parse_conv(char *str, t_conv *node)
{
	int		i;

	i = 1;
	if (*++str == '%')
	{
		node->type = percent;
		return (2);
	}
	ft_putnbr(i);
	ft_putchar(*str);
	ft_putstr("C\n");
	delay(500);
	parse_flags(&str, node, &i);
	ft_putnbr(i);
	ft_putchar(*str);
	ft_putstr("D\n");
	delay(500);
	if (!parse_wp(&str, node, &i))
		return (0);
	ft_putnbr(i);
	ft_putchar(*str);
	ft_putstr("E\n");
	delay(500);
	parse_len(&str, node, &i);
	ft_putnbr(i);
	ft_putchar(*str);
	ft_putstr("F\n");
	delay(500);

	if (*str == 'S' || *str == 'D' || *str == 'O' || *str == 'U' || *str == 'C')
	{
		if (node->length && !(node->length & 0x08))
			return (0);
		else
			node->length = 0x08;
	}
	ft_putnbr(i);
	ft_putchar(*str);
	ft_putstr("G\n");
	printf("prefix is \"%s\", flags %x, width = %d, precision = %d, length = %x\n",
			node->prefix, node->flags, node->width, node->precision, node->length);
	delay(500);
	if ((*str == 's' || *str == 'S') && ++i && str++)
		node->type = conv_s;
	else if ((*str == 'd' || *str == 'D') && ++i && str++)
		node->type = conv_d;
	else if ((*str == 'o' || *str == 'O') && ++i && str++)
		node->type = conv_o;
	else if ((*str == 'u' || *str == 'U') && ++i && str++)
		node->type = conv_u;
	else if (*str == 'p' && ++i && str++)
		node->type = conv_p;
	else if (*str == 'i' && ++i && str++)
		node->type = conv_i;
	else if (*str == 'x' && ++i && str++)
		node->type = conv_x;
	else if (*str == 'X' && ++i && str++)
		node->type = conv_X;
	else if (*str == 'c' && ++i && str++)
		node->type = conv_c;
	else
		return (0);
	ft_putnbr(i);
	ft_putstr("H\n\n");
	delay(500);
	return (i);
}

t_conv	*pf_chomp(char *str, char *error)
{
	t_conv	*node;
	int		i;

	ft_putstr("pf_chomp\n");
	i = ft_strlen_c(str, '%');
	node = new_conv(i, str);
	str += i;
	ft_putnbr(*error);
	ft_putstr("A\n");
	delay(500);
	if (*str && !*error)
	{
		if (!(i = parse_conv(str, node)))
			*error = 1;
		str += i;
		ft_putstr(str);
		ft_putstr(" | B\n");
		delay(500);
		if (*str && !*error)
			node->next = pf_chomp(str, error);
	}
	if (*error)
	{
		ft_putstr("Error!\n");
		free(node->prefix);
		free(node);
		return (NULL);
	}
	return (node);
}
