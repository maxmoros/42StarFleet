/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:59:02 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/28 21:46:30 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
 
int		ft_printf(char *str, ...)
{
	t_conv	*node;
	va_list	ap;
	char	error;
	
	error = 0;
	node = pf_chomp(str, &error);
	va_start(ap, str);
//	print_nodes(node);
	do_conv(ap, node, &error);
	va_end(ap);
	return (error ? 0 : 1);
}

int		main()//int ac, char **av)
{
	ft_printf("|%d|\n", 343);
	printf("|%d|\n", 343);
	ft_putchar('\n');
	ft_printf("|%ld|\n", -3333333333);
	printf("|%ld|\n", 3333333333);
	ft_putchar('\n');
	ft_printf("|%c|\n", '#');
	printf("|%c|\n", '#');
	ft_putchar('\n');
	ft_printf("|%c|\n", '#');
	printf("|%c|\n", '#');
	ft_putchar('\n');
	ft_printf("|%s|\n", "HELLO");
	printf("|%s|\n", "HELLO");
	ft_putchar('\n');
	ft_printf("|%p|\n", (void*)255);
	printf("|%p|\n", (void*)255);
	ft_putchar('\n');
	ft_printf("|%d|\n", 3234);
	printf("|%d|\n", 3234);
	ft_putchar('\n');
	ft_printf("|%o|\n", 255);
	printf("|%o|\n", 255);
	ft_putchar('\n');
	ft_printf("|%u|\n", 1234567);
	printf("|%u|\n", 1234567);
	ft_putchar('\n');
	ft_printf("|%x|\n", 255);
	printf("|%x|\n", 255);
	ft_putchar('\n');

	return (0);
}
