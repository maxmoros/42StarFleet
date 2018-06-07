/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:31:02 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/28 14:03:48 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *ts;
	unsigned char *td;
	unsigned char x;

	ts = (unsigned char*)src;
	td = (unsigned char*)dst;
	x = (unsigned char)c;
	while (n > 0 && (*td++ = *ts++) != x)
		n--;
	if (n == 0)
		return (NULL);
	return (td);
}
