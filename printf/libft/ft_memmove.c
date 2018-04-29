/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 20:38:20 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/28 14:01:47 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *td;
	unsigned char *ts;

	td = (unsigned char*)dst;
	ts = (unsigned char*)src;
	if (len)
	{
		if (src < dst)
			while (len--)
				td[len] = ts[len];
		else
			while (len--)
				*td++ = *ts++;
	}
	return (dst);
}
