/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/12 12:18:37 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			print_nodes(t_dir *node)
{
	t_dir	*tmp;

	if (FLAG_SET(L_FLAG))
		print_longf_nodes(node);
	else if (FLAG_SET(A_FLAG) || node->next->next)
	{
		tmp = node;
		while (tmp)
		{
			if (FLAG_SET(A_FLAG) || NAME(tmp)[0] != '.')
			{
				if (FLAG_SET(S_FLAG))
					ft_pbs("%d ", BLOCKS(tmp));
				ft_pbs("%s\t", NAME(tmp));
			}
			tmp = tmp->next;
		}
		write(1, "\n", 1);
	}
}

int				check_symlink(char *path)
{
	struct stat		stat;

	g_root_offset ? free(g_root_offset) : 0;
	g_root_offset = NULL;
	if (lstat(path, &stat))
		return (0);
	return (S_ISLNK(stat.st_mode));
}

void			print_symlink(char *path)
{
	t_dir			*node;
	char			buff[PATH_MAX + 1];

	node = new_dir(path, NULL, NULL, 0);
	FLAG_SET(S_FLAG) ? write(1, "1 ", 2) : 0;
	print_permissions(node->stat);
	write(1, "@", 1);
	print_id(node);
	print_size(node, 2);
	print_date_mod(node);
	ft_putstr(path);
	buff[readlink(node->path, buff, PATH_MAX)] = '\0';
	ft_pbs(" -> %s\n", buff);
	free(node);
}
