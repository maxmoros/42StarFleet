/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:43:48 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/10 16:01:18 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*g_root_offset;
uint8_t	g_flags;

char	parse_flags(char *input)
{
	while (*++input)
	{
		if (*input == 'l')
			g_flags |= L_FLAG;
		else if (*input == 'R')
			g_flags |= RC_FLAG;
		else if (*input == 'a')
			g_flags |= A_FLAG;
		else if (*input == 'r')
			g_flags |= RV_FLAG;
		else if (*input == 't')
			g_flags |= T_FLAG;
		else if (*input == 's')
			g_flags |= S_FLAG;
		else
		{
			ft_putstr("    ft_ls: illegal option -- \'");
			ft_putchar(*input);
			ft_putstr("\'\n");
			return (0);
		}
	}
	return (1);
}

DIR		*parse_input(uint8_t *verbose_title, char ***input)
{
	g_root_offset = ft_strdup(*input && **input ? **input : ".");
	if (**input && *(*input + 1) && !*verbose_title)
		*verbose_title = 1;
	return (opendir(g_root_offset));
}

void	rev_order(char **input)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	while (input[++j])
		;
	while (++i < --j)
	{
		tmp = input[j];
		input[j] = input[i];
		input[i] = tmp;
	}
}

void	ls(char **input, uint8_t verbose_title)
{
	DIR				*dir;
	t_dir			*root;

	if (FLAG_SET(RV_FLAG))
		rev_order(input);
	while (input && *input)
		if (!(dir = parse_input(&verbose_title, &input)))
		{
			ft_putstr("ft_ls: ");
			ft_putstr(*input++);
			ft_putstr(": No such file or directory\n");
		}
		else if (0)
			;		//DO SYMLINK HERE?
		else	
		{
			if (verbose_title)
			{
				ft_putstr(*input);
				ft_putstr(":\n");
			}
			print_nodes((root = get_nodes(dir, NULL)));
			write(1, "\n", *++input && !FLAG_SET(L_FLAG));
			closedir(dir);
		}
}

int		main(int ac, char **av)
{
	char	**tmp;

	g_flags = 0;
	(void)ac;
	while (*++av && **av == '-')
		if (!parse_flags(*av))
		{
			ft_putstr("        Usage: ft_ls [-alrRt] [file ...]\n");
			return (0);
		}
	if (*av)
		ls(av, 0);
	else
	{
		if (!(tmp = (char**)ft_memalloc(sizeof(char*) * 2)))
			return (0);
		tmp[0] = ft_strdup(".");
		ls(tmp, 0);
		free(tmp[0]);
		free(tmp);
	}
	free(g_root_offset);
	return (0);
}
