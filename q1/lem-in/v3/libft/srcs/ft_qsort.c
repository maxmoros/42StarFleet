/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 20:37:10 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/05 07:48:53 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qsort(int *tab, unsigned int size)
{
	int pl;
	int pr;
	int i;

	pl = 0;
	pr = size - 1;
	i = 0;
	if (size > 2)
	{
		while (i < pr)
		{
			if (tab[i] <= tab[pr])
			{
				ft_math_swap(&tab[pl], &tab[i]);
				pl++;
			}
			i++;
		}
		ft_math_swap(&tab[pl], &tab[pr]);
		ft_qsort(&tab[0], pl);
		ft_qsort(&tab[pl], size - pl);
	}
	if (size == 2 && tab[0] > tab[1])
		ft_math_swap(&tab[0], &tab[1]);
}
