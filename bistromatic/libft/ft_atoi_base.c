/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:44:04 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/08 21:17:34 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_normalize(char *str, char *base, int radix)
{
	int		i;
	int		swap;

	while (*str)
	{
		i = -1;
		swap = 1;
		while (++i < radix && swap)
		{
			if (*str == base[i] && swap--)
				*str = 'a' + i;
		}
		str++;
	}
}

int		ft_atoi_base(const char *str, char *base)
{
	unsigned int		out;
	int					sign;
	int					rad;
	char				*copy;

	copy = ft_strdup(str);
	rad = ft_strlen(base);
	ft_normalize(copy, base, rad);
	out = 0;
	while (*copy == 32 || (*copy > 8 && *copy < 14))
		copy++;
	if (!((sign = 1) && *copy == '+' && (*++copy < 'a' || *copy > 'a' + rad)))
	{
		if (rad == 10 && *copy == '-' && copy++)
			sign = -1;
		while (*copy >= 'a' && *copy <= 'a' + rad)
		{
			out *= rad;
			out += *copy++ - 'a';
		}
	}
//	free(copy);
	return (out * sign);
}
