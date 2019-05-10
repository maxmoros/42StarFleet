/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:08:48 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 18:34:50 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int		print_usage()
{
	ft_putstr("\033[31;1mDon't do that please\033[0m\n");
	return (0);
}

int		ooo(int argc, char **argv)
{
	if (!argc && g_ft_ssl.flags & FLAG_S)
		return (1);
	if (!argc || g_ft_ssl.flags & FLAG_P)
		read_fd(0);
	if (g_ft_ssl.flags & FLAG_S && argc--)
		read_str(*argv++);
	while (argc-- > 0)
		read_file(*argv++);
	return (0);
}

int		main(int ac, char **av)
{
	char	**args;
	int		argc;

	g_ft_ssl.debug = 1;
	args = av + 1;
	argc = ac - 2;
	if (ac < 2 || set_hash(*args++) || (ac > 2 && set_flags(&argc, &args)))
		return (print_usage());
	init_md5();
	init_sha256();
	if (ooo(argc, args))
		return (print_usage());
	return (0);
}
