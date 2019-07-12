/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pbs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:52:16 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/11 13:43:17 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int		ft_pbs(char *f, ...)
{
	va_list		ap;

	if (!f)
		return (-1);
	va_start(ap, f);
	while (*f)
	{
		while (*f && *f != '%')
			write(1, f++, 1);
		if (*f && (*++f == 'c' || *f == 's' || *f == 'd'))
		{
			if (*f == 'c')
				ft_putchar(va_arg(ap, int));
			else if (*f == 's')
				ft_putstr(va_arg(ap, char *));
			else if (*f == 'd')
				ft_putnbr(va_arg(ap, int));
			else
				ft_putstr("\033[31m\n\nft_pbs: bad format type\n\033[0m");
			f++;
		}
	}
	va_end(ap);
	return (0);
}
