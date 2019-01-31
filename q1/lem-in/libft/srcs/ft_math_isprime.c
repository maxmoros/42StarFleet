/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_isprime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:38:42 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/07 19:39:56 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_math_isprime(unsigned int num)
{
	unsigned int	i;
	unsigned int	sqrt;

	if (num < 2)
		return (0);
	i = 1;
	sqrt = ft_math_sqrt_t(num);
	while (++i <= sqrt)
		if (num % i == 0)
			return (0);
	return (1);
}
