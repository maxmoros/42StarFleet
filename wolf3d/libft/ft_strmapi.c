/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:00:58 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/25 19:24:24 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*output;

	i = 0;
	if (s && f)
	{
		while (s[i++])
			;
		if (!(output = (char*)malloc(sizeof(char) * i)))
			return (NULL);
		output[--i] = '\0';
		while (i--)
			output[i] = (*f)(i, s[i]);
		return (output);
	}
	return (NULL);
}
