/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:23:28 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:26:57 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ph;
	char	*pn;
	char	*phh;

	if (!*needle)
		return ((char*)haystack);
	len++;
	while (*haystack && --len && !(phh = NULL))
		if (*haystack == *needle)
		{
			ph = (char*)haystack;
			pn = (char*)needle;
			while (*++haystack == *++needle && *haystack && --len)
				if (*haystack == *pn && !phh)
					phh = (char*)haystack;
			if (!*needle)
				return (ph);
			needle = pn;
			if (phh && (len += haystack - phh))
				haystack = phh;
		}
		else
			haystack++;
	return (NULL);
}
