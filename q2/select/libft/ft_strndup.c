/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:20:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/07 18:44:32 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*output;

	if (!(output = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	output[n] = '\0';
	while (n--)
		output[n] = s1[n];
	return (output);
}
