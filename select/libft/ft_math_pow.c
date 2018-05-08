/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_pow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:11:56 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/01 18:32:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_math_powr(int i, int p)
{
	if (p % 2 == 0)
		return (ft_math_powr(i * i, p / 2));
	if (p % 3 == 0)
		return (ft_math_powr(i * i * i, p / 3));
	if (p % 5 == 0)
		return (ft_math_powr(i * i * i * i * i, p / 5));
	if (p == 1)
		return (i);
	return (i * ft_math_powr(i, p - 1));
}

int			ft_math_pow(int i, int p)
{
	if (p == 0)
		return (1);
	if (p < 0)
		return (1 / ft_math_powr(i, -p));
	return (ft_math_powr(i, p));
}
