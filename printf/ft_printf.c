/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 12:59:02 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/26 20:02:15 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <time.h>
 
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
	va_list	ap;
	int		d;
	char	c;
	char	*s;
	
	va_start(ap, str);
	while (*str)
		switch(*str++) {
			case 's':                       
				s = va_arg(ap, char *);
				ft_putstr(s);
				 break;
			case 'd':                       
				d = va_arg(ap, int);
				ft_putnbr(d);
				break;
			case 'c':                      
				c = va_arg(ap, int);
				ft_putchar(c);
			   break;
	   }
	va_end(ap);
	return (1);
}

int		main(int ac, char **av)
{
	char	error;
	t_conv	*node;

	error = 0;
	if (ac == 2)
	{
		ft_putstr("\n");
		node = pf_chomp(av[1], &error);
		ft_putstr("\n");
		print_nodes(node);
	}
	return (0);
}
