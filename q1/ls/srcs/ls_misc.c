/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_misc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:03:49 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/09 18:10:18 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

uint8_t		ft_numlen(int num)
{
	uint8_t		len;

	len = (num ? 0 : 1);
	while (num && ++len)
		num /= 10;
	return (len);
}