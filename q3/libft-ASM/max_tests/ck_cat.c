/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_cat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:31:02 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:31:04 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_cat(FILE *tests[3])
{
	char	*gnl;
	char	*ret;
	FILE	*file;

	freopen("/tmp/cat_test", "w", stdout);
	ft_cat(fileno(tests[0]));
	ft_cat(fileno(tests[1]));
	ft_cat(fileno(tests[2]));
	ft_cat(-1);
	freopen("/dev/tty", "w", stdout);
	file = fopen("/tmp/cat_test", "r");
	gnl = calloc(100, 1);
	ret = fgets(gnl, 19, file);
	assert(ret != NULL);
	assert(!strcmp(ret, "424242maxmax"));
	fclose(file);
	freopen("/tmp/cat_test", "w", stdout);
	ft_cat(0);
	freopen("/dev/tty", "w", stdout);
	file = fopen("/tmp/cat_test", "r");
	ret = fgets(gnl, 99, file);
	ft_putstr("\nGot \'");
	ft_putstr(ret);
	ft_putstr("\' on FD 0\n");
	free(gnl);
}

void			ck_cat(void)
{
	FILE	*tests[3];

	ft_putstr("Give ft_cat input on FD 0: ");
	tests[0] = fopen("/tmp/test0.txt", "w+");
	tests[1] = fopen("/tmp/test1.txt", "w+");
	tests[2] = fopen("/tmp/test2.txt", "w+");
	fprintf(tests[0], "424242");
	rewind(tests[0]);
	fprintf(tests[1], "maxmax");
	rewind(tests[1]);
	test_cat(tests);
	fclose(tests[0]);
	fclose(tests[1]);
	fclose(tests[2]);
	ft_putstr("ft_cat: \x1b[32mOK!\x1b[0m\n");
}
