/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:59:02 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/27 19:24:16 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <time.h>
#include <stdio.h>
 
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 100 * number_of_seconds;
 
    // Stroing start time
    clock_t start_time = clock();
 
    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

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
	int		x = 12321;

	ft_printf("the %d number is %d\n", 343, x);
	ft_printf("the %ld number is %d\n", 3333333333, x);
	printf("the %ld number is %d\n", 3333333333, x);
	ft_printf("|%-+0#06.96c|\n", '#');
	printf("|%6lc|\n", '#');
	return (0);
}
