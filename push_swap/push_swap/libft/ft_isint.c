/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:19:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/21 14:16:15 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isnum(char *num)
{
	while (*num == ' ')
		num++;
	if (*num == '+' || *num == '-')
		num++;
	while (*num)
		if (!ft_isdigit(*num))
			return (0);
		else
			num++;
	return (1);
}

static int	equ_num_int(char *num)
{
	int		atoi;
	int		sign;
	char	*start;

	atoi = ft_atoi(num);
	while (*num == ' ')
		num++;
	sign = 0;
	if (*num == '+' || *num == '-')
		if (*num++ == '-')
			sign = 1;
	start = num;
	if ((sign && atoi > 0) || (!sign && atoi < 0))
		return (0);
	while (ft_isdigit(*(num + 1)))
		num++;
	while (num >= start)
		if (*num-- - '0' != ft_math_abs(atoi % 10))
			return (0);
		else
			atoi /= 10;
	return (1);
}

int			ft_isint(char *str)
{
	if (!isnum(str))
		return (0);
	return (equ_num_int(str));
}
