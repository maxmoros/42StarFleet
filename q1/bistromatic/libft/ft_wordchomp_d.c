/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordchomp_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 11:17:09 by mmoros            #+#    #+#             */
/*   Updated: 2018/03/01 17:48:03 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wordchomp_d(char **str, char d)
{
	char	*word;
	char	*out;
	int		i;

	if (!str || !*str)
		return (NULL);
	if (**str == d)
		while (*++*str == d)
			;
	if (!**str)
		return (NULL);
	i = 0;
	while (str[0][i] && str[0][i] != d)
		i++;
	if (!(word = (char*)malloc(sizeof(char) * ++i)))
		return (NULL);
	word[--i] = '\0';
	out = word;
	while (i--)
		*word++ = *(str[0]++);
	return (out);
}
