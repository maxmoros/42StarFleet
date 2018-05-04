/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:43:48 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/04 14:52:30 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	parse_flags(char *flags, char *input)
{
	while (++input)
	{
		if (*input == 'l')
			*flags |= 0x1;
		else if (*input == 'R')
			*flags |= 0x2;
		else if (*input == 'a')
			*flags |= 0x4;
		else if (*input == 'r')
			*flags |= 0x8;
		else if (*input == 't')
			*flags |= 0x10;
		else
			return (0);
	}
	return (1);
}

DIR		*parse_input(char *flags, char **input)
{
	DIR		*dir;

	while (input && **input == '-')
		parse_flags(flags, *input++);
	if ((dir = opendir(*input)))
		return (dir);
	return (NULL);
}

int		ls(char **input)
{
	DIR				*dir;
	struct dirent	*dp;
	char			flags;

	flags = 0;
	if (!(dir = parse_input(&flags, input)) ||
		!(dp = readdir(dir)))
		return (0);
	ft_putstr("flags set : ");
	ft_puthex(flags);
	ft_putchar('\n');
	return (1);
}

int		main(int ac, char **av)
{
	if (ac > 1)
		ls(av + 1);
	return (0);
}
