/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:30:19 by mmoros            #+#    #+#             */
/*   Updated: 2018/02/28 20:30:24 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	while (++i < n && s1[i] == s2[i] && s1[i])
		;
	if (s1[i] == s2[i] || i == n)
		return (1);
	return (0);
}
