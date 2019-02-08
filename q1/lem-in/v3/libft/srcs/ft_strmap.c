/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:42:25 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:22:43 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*output;

	if (s && f)
	{
		i = -1;
		while (s[++i])
			;
		i++;
		if (!(output = (char*)malloc(sizeof(char) * i)))
			return (NULL);
		output[--i] = '\0';
		while (i--)
			output[i] = (f)(s[i]);
		return (output);
	}
	return (NULL);
}
