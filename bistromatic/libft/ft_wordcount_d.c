/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:31:03 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/07 18:46:52 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcount_d(char const *s, char d)
{
	int count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == d && *++s)
			;
		if (*s && *s != d && ++count)
			while (*s != d && *++s)
				;
	}
	return (count);
}
