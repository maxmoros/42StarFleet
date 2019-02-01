/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:43:11 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:45:24 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static char *g_d1;
static char *g_d2;
static char *g_src;

static void		test_strcat(size_t dlen, size_t slen)
{
	char	*ret;

	g_src[slen] = '\0';
	memset(g_d1, 'a', dlen);
	memset(g_d2, 'a', dlen);
	g_d1[dlen] = '\0';
	g_d2[dlen] = '\0';
	strcat(g_d1, g_src);
	ret = ft_strcat(g_d2, g_src);
	if (g_d2 != ret || memcmp(g_d1, g_d2, 21))
	{
		ft_putstr("\x1b[31mKO!\x1b[0m\n");
		ft_putstr("failed at dlen=\'");
		ft_putnbr((int)dlen);
		ft_putstr(", slen=\'");
		ft_putnbr((int)slen);
		ft_putstr("\'\n");
	}
	assert(g_d2 == ret);
	assert(!memcmp(g_d1, g_d2, 21));
	g_src[slen] = '!';
}

void			ck_strcat(void)
{
	ft_putstr("ft_strcat: ");
	g_d1 = calloc(21, 1);
	g_d2 = calloc(21, 1);
	g_src = calloc(11, 1);
	memset(g_src, 'x', 9);
	test_strcat(0, 0);
	test_strcat(0, 1);
	test_strcat(1, 0);
	test_strcat(1, 1);
	test_strcat(0, 9);
	test_strcat(9, 0);
	test_strcat(9, 9);
	free(g_d1);
	free(g_d2);
	free(g_src);
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
