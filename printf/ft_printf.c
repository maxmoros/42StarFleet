/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:59:02 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 23:33:59 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
 
int		ft_printf(char *str, ...)
{
	t_conv	*node;
	va_list	ap;
	char	error;
	int		sum;
	
	error = 0;
	node = pf_chomp(str, &error);
	va_start(ap, str);
	do_conv(ap, node, &error);
	sum = sum_printed(node);
	node = free_conv(node);
	va_end(ap);
	return (sum);
}
