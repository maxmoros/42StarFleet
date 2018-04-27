/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 21:02:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 21:27:43 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putdig(int n)
{
	if (!n)
		return ;
	ft_putdig(n / 10);
	ft_putchar('0' + n % 10);
}

void		ft_putnbr(int n)
{
	if (!n)
		write(1, "0", 1);
	else if (n == -2147483648)
	{
		write(1, "-", 1);
		ft_putdig(21474);
		ft_putdig(83648);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(1, "-", 1);
	}
	ft_putdig(n);
}
