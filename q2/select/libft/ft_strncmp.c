/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:20:14 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/24 18:04:27 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)s1;
	b = (unsigned char*)s2;
	if (!n)
		return (0);
	if (*a != *b)
		return (*a - *b);
	while (--n && *++a == *++b && *a)
		;
	return (*a - *b);
}
