/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:47:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:02:28 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *tmp;

	tmp = (char *)s;
	while (*tmp++)
		;
	tmp--;
	while (*tmp != c && --tmp != s - 1)
		;
	if (*tmp == c)
		return (tmp);
	return (NULL);
}
