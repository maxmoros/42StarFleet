/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:53:13 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:05:00 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*tmp;

	tmp = dst;
	len++;
	while (*src && --len)
		*tmp++ = *src++;
	if (!*src)
		while (--len)
			*tmp++ = '\0';
	return (dst);
}
