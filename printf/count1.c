/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 21:31:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/28 21:44:29 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_oct(uintmax_t oct)
{
	int		count;

	if (!oct)
		return (1);
	count = 0;
	while (oct)
	{
		count++;
		oct /= 8;
	}
	return (count);
}

static int	dig_bigoct(uintmax_t oct)
{
	int		count;

	if (oct)
	{
		count = 1 + dig_bigoct(oct / 8);
		ft_putchar('0' + oct % 8);
		return (count);
	}
	return (0);
}

int			put_bigoct(uintmax_t oct)
{
	if (!oct)
	{
		ft_putchar('0');
		return (1);
	}
	return (dig_bigoct(oct));
}
