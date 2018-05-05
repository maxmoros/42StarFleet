/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:43:48 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/04 19:48:56 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	parse_flags(char *flags, char *input)
{
	while (++input)
	{
		if (*input == 'l')
			*flags |= L_FLAG;
		else if (*input == 'R')
			*flags |= RC_FLAG;
		else if (*input == 'a')
			*flags |= A_FLAG;
		else if (*input == 'r')
			*flags |= RV_FLAG;
		else if (*input == 't')
			*flags |= T_FLAG;
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
	char			flags;
	t_dir			*root;

	flags = 0;
	if (!(dir = parse_input(&flags, input)))
		return (0);
	root = get_nodes(dir, flags);
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
