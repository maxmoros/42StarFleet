/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:31:38 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:31:40 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_memcpy(size_t n, char *starmap)
{
	char	*my_s;
	char	*sy_s;
	char	*return_check;

	my_s = calloc(n + 1, 1);
	sy_s = calloc(n + 1, 1);
	return_check = ft_memcpy(my_s, starmap, n);
	memcpy(sy_s, starmap, n);
	if (return_check != my_s)
		ft_putstr("failed to return correct pointer\n");
	assert(return_check == my_s);
	if (strcmp(my_s, sy_s))
	{
		ft_putstr("failed to copy correct data with length = \'");
		ft_putnbr((int)n);
		ft_putstr("\'\n");
	}
	assert(!strcmp(my_s, sy_s));
}

void			ck_memcpy(void)
{
	char	*starmap;

	ft_putstr("ft_memcpy: ");
	starmap = calloc(100, 1);
	memset(starmap, '*', 99);
	test_memcpy(0, starmap);
	test_memcpy(1, starmap);
	test_memcpy(50, starmap);
	test_memcpy(99, starmap);
	free(starmap);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
