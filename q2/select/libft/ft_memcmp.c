/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:48:15 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:30:02 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t1;
	unsigned char	*t2;
	size_t			i;

	t1 = (unsigned char*)s1;
	t2 = (unsigned char*)s2;
	i = -1;
	while (++i < n && t1[i] == t2[i])
		;
	if (i != n)
		return (t1[i] - t2[i]);
	return (0);
}
