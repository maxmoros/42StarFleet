/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_median.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 11:40:11 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 18:01:17 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_median(int *tab, int size)
{
	int		*set;

	if (!(set = (int*)ft_memalloc(sizeof(int) * size)))
		return (0x7FFFFFFF);
	ft_memcpy(set, tab, size * 4);
	ft_qsort(set, size);
	return (set[size / 2]);
}
