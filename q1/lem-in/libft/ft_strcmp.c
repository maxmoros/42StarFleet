/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 19:13:52 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:03:33 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)s1;
	b = (unsigned char*)s2;
	if (*a != *b)
		return (*a - *b);
	while (*++a == *++b && *a)
		;
	return (*a - *b);
}
