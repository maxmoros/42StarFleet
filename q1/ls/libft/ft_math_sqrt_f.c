/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_sqrt_f.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:16:08 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/07 20:51:59 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_math_sqrt_f(unsigned const int a)
{
	unsigned int	est;

	est = 1;
	while (est * est < a)
		est++;
	return (est);
}
