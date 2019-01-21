/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 19:16:39 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:29:39 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*output;

	output = NULL;
	if (size > 0)
	{
		output = malloc(sizeof(char) * (size));
		if (output)
			while (size-- > 0)
				output[size] = 0x00;
	}
	return (output);
}
