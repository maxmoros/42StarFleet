/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convf1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 20:23:44 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/24 20:26:53 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		percent(t_conv *node)
{
	return (node->width);
}

int		conv_s(t_conv *node)
{
	return (node->width);
}

int		conv_d(t_conv *node)
{
	return (node->width);
}

int		conv_o(t_conv *node)
{
	return (node->width);
}

int		conv_u(t_conv *node)
{
	return (node->width);
}

int		conv_p(t_conv *node)
{
	return (node->width);
}

int		conv_i(t_conv *node)
{
	return (node->width);
}

int		conv_x(t_conv *node)
{
	return (node->width);
}

int		conv_X(t_conv *node)
{
	return (node->width);
}

int		conv_c(t_conv *node)
{
	return (node->width);
}
