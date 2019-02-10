/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:16:41 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/27 19:37:09 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	count;

	if (n == 0)
		return (2);
	count = 1;
	if (n < 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*out;
	int		len;

	len = ft_nbrlen(n);
	if (!(out = (char*)malloc(sizeof(char) * len--)))
		return (NULL);
	out[len] = '\0';
	if (n < 0)
	{
		out[0] = '-';
		while (len-- > 1)
		{
			out[len] = '0' - n % 10;
			n /= 10;
		}
	}
	else
		while (len--)
		{
			out[len] = '0' + n % 10;
			n /= 10;
		}
	return (out);
}
