/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 21:45:07 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/01 17:07:06 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**output;
	int		i;
	int		wc;

	wc = ft_wordcount_d(s, c);
	if (!s || !(output = (char**)malloc(sizeof(char*) * (wc + 1))))
		return (NULL);
	i = -1;
	while (++i < wc)
		output[i] = ft_wordchomp_d((char**)&s, c);
	output[i] = NULL;
	return (output);
}
