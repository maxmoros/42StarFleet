/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 20:39:43 by mmoros            #+#    #+#             */
/*   Updated: 2019/01/29 20:39:45 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asmtests.h"

static void		test_puts(char *str)
{
	int		len;
	int		i;
	char	*line;
	char	*read;
	FILE	*file;

	if (str == NULL)
		str = "(null)";
	len = strlen(str);
	line = calloc(len + 2, 1);
	freopen("/tmp/test", "w", stdout);
	ft_puts(str);
	freopen("/dev/tty", "w", stdout);
	file = fopen("/tmp/test", "r");
	read = fgets(line, len + 2, file);
	assert(read != NULL);
	i = strcspn(read, "\n");
	assert(i == len);
	read[i] = '\0';
	if (strcmp(read, str))
		ft_putstr("failed to put correct data to stdout.\n");
	assert(!strcmp(read, str));
	free(line);
	fclose(file);
}

void			ck_puts(void)
{
	ft_putstr("ft_puts: ");
	test_puts("");
	test_puts(NULL);
	test_puts("*************************************************************");
	ft_putstr("\x1b[32mOK!\x1b[0m\n");
}
