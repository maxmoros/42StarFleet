/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_gcd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:12:57 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/01 18:36:01 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_math_gcd(int a, int b)
{
	int		i;

	if (a < 0)
		a *= -1;
	if (b < 0)
		b *= -1;
	if (b < a)
		ft_math_swap(&a, &b);
	if (b % a == 0)
		return (a);
	if (b % (a / 2) == 0)
		return (a / 2);
	if (b % (a / 3) == 0)
		return (a / 3);
	if (b % (a / 5) == 0)
		return (a / 5);
	i = a / 5;
	while (--i)
		if (a % i == 0 && b % i == 0)
			return (i);
	return (0);
}
