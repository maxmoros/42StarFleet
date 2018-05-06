/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/05 19:42:22 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	recurse_print(t_dir *node, char flags)
{
	struct stat		stats;
	char			*path;
	
	while (node)
	{
		if (ft_strcmp(node->data->d_name, ".") &&
			ft_strcmp(node->data->d_name, ".."))
		{
			path = node_path(node);
			if (stat(path, &stats) == -1)
				return ;
			if (stats.st_mode & S_IFDIR)
			{
				ft_putstr("\n\n./");
				ft_putstr(path);
				ft_putstr(":\n");
				print_nodes(node->in, flags);
			}
			free(path);
		}
		node = node->next;
	}
}

void	print_longf_nodes(t_dir *node, char flags)
{
//	struct stat		stats;

	while  (node)
	{
		;
	}
	ft_putstr(node->data->d_name);
	flags &= L_FLAG;
}

void	print_nodes(t_dir *node, char flags)
{
	t_dir	*tmp;

	tmp = node;
	if (flags & L_FLAG)
		print_longf_nodes(node, flags);
	else
		while (tmp)
		{
	//		ft_putstr(tmp->data->d_name);
			if (flags & A_FLAG || tmp->data->d_name[0] != '.')
			{
				ft_putstr(tmp->data->d_name);
				ft_putchar('\t');
			}
			tmp = tmp->next;
		}
	if (flags & RC_FLAG)
		recurse_print(node, flags);
}
