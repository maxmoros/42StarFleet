/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 19:59:14 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:03:14 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *td;
	unsigned char *ts;

	ts = (unsigned char*)src;
	td = (unsigned char*)dst;
	while (n-- > 0)
		*td++ = *ts++;
	return (dst);
}
