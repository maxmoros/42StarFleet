/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:56:47 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 11:49:49 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	char	*str;
	int		i;
	int		j;

	output = NULL;
	if (s1 && s2)
	{
		i = 0;
		j = 0;
		while (s1[i])
			i++;
		while (s2[j])
			j++;
		if (!(str = (char*)malloc(sizeof(char) * (i + j + 1))))
			return (NULL);
		output = str;
		str[i + j] = '\0';
		while (j--)
			str[i + j] = s2[j];
		while (i--)
			str[i] = s1[i];
		return (output);
	}
	return (NULL);
}
