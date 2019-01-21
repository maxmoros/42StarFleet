/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 21:15:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/12 20:40:58 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_puthexdig(unsigned int hex)
{
	if (hex)
	{
		ft_puthexdig(hex / 16);
		if (hex % 16 > 9)
			ft_putchar('A' + hex % 16 - 10);
		else
			ft_putchar('0' + hex % 16);
	}
}

void		ft_puthex(unsigned int hex)
{
	ft_putstr("0x");
	if (hex == 0)
		ft_putchar('0');
	else
		ft_puthexdig(hex);
}
