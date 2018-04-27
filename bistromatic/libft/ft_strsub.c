/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:46:05 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/25 19:56:25 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*output;

	if (s)
	{
		if (!(output = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		output[len] = '\0';
		while (len--)
			output[len] = s[start + len];
		return (output);
	}
	return (NULL);
}
