/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:15:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/28 15:02:26 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putoctdig(unsigned int oct)
{
	int		count;

	count = 0;
	if (oct)
	{
		count += 1 + ft_putoctdig(oct / 8);
		ft_putchar('0' + oct % 8);
	}
	return (count);
}

int			ft_putoct(unsigned int oct)
{
	if (oct == 0)
		ft_putchar('0');
	else
		return (ft_putoctdig(oct));
	return (1);
}
