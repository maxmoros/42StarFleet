/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:33:54 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:33:59 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_strdup(size_t n, char *starmap)
{
	char	*test_s;
	char	*my_s;

	test_s = calloc(n + 1, 1);
	strncpy(test_s, starmap, n);
	my_s = ft_strdup(test_s);
	if (my_s == test_s)
		ft_putstr("failed to return new pointer OR didn't alocate new mem\n");
	assert(my_s != test_s);
	if (strcmp(my_s, test_s))
	{
		ft_putstr("failed to copy correct data with length = \'");
		ft_putnbr((int)n);
		ft_putstr("\'\n");
	}
	assert(!strcmp(my_s, test_s));
	free(test_s);
	free(my_s);
}

void			ck_strdup(void)
{
	char	*starmap;

	ft_putstr("ft_strdup: ");
	starmap = calloc(100, 1);
	memset(starmap, '*', 99);
	test_strdup(0, starmap);
	test_strdup(1, starmap);
	test_strdup(50, starmap);
	test_strdup(99, starmap);
	free(starmap);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
