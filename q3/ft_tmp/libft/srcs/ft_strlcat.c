/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 11:39:58 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/07 18:42:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;

	d = ft_strlen(dst);
	s = ft_strlen((char*)src);
	if (dstsize < d + 1)
		return (s + dstsize);
	if (dstsize > d + 1)
	{
		i = d;
		while (i < dstsize - 1 && *src)
			dst[i++] = *src++;
		dst[i] = '\0';
	}
	return (s + d);
}
