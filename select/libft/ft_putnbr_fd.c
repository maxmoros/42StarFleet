/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:22:10 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/01 15:00:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putdig_fd(unsigned int n, int fd)
{
	if (n > 9)
		ft_putdig_fd(n / 10, fd);
	ft_putchar_fd('0' + n % 10, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	unsigned int i;

	if (n < 0 && (i = -n))
		ft_putchar_fd('-', fd);
	else
		i = n;
	ft_putdig_fd(i, fd);
}
