/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:43:48 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/09 19:01:06 by mmoros           ###   ########.fr       */
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
		else
			return (0);
	}
	return (1);
}

DIR		*parse_input(char **input)
{
	while (input && *input && **input == '-')
		parse_flags(*input++);
	g_root_offset = ft_strdup(input && *input ? *input : ".");
	return (opendir(g_root_offset));
}

void	bs_print(t_dir *node, int ind)
{
	while (node)
	{
		write(1, "                                              ", ind * 2);
		printf("n->path = \'%s\'\n", node->path);
		if (node->in)
			bs_print(node->in, ind + 1);
		node = node->next;
	}
}

int		ls(char **input)
{
	DIR				*dir;
	t_dir			*root;

	g_flags = 0;
	if (!(dir = parse_input(input)))
		return (0);
	root = get_nodes(dir, NULL);
//	bs_print(root, 0);
	print_nodes(root);
	write(1, "\n", 1);
	free(g_root_offset);
	return (1);
}

int		main(int ac, char **av)
{
	printf("\033[31;5;205mSTART\033[m\n");
	ls(ac > 1 ? av + 1 : NULL);
	return (0);
}
