/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:35:24 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:16:19 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*ph;
	char	*pn;
	char	*phh;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack && !(phh = NULL))
		if (*haystack == *needle)
		{
			ph = (char*)haystack;
			pn = (char*)needle;
			while (*++haystack == *++needle && *haystack)
				if (*haystack == *pn && !phh)
					phh = (char*)haystack;
			if (!*needle)
				return (ph);
			needle = pn;
			if (phh)
				haystack = phh;
		}
		else
			haystack++;
	return (NULL);
}
