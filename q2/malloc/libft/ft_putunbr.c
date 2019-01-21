/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 21:02:32 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/27 18:59:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putdig(unsigned int n)
{
	int		count;

	count = 1;
	if (!n)
		return (0);
	count += ft_putdig(n / 10);
	ft_putchar('0' + n % 10);
	return (count);
}

int			ft_putunbr(unsigned int n)
{
	if (!n)
		write(1, "0", 1);
	else
		return (ft_putdig(n));
	return (1);
}
