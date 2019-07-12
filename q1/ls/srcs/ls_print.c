/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/11 21:35:19 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		recurse_print(t_dir *node)
{
	while (node)
	{
		if ((FLAG_SET(A_FLAG) || !(NAME(node)[0] == '.')) &&
				CMP_DIR(".") && CMP_DIR("..") && S_ISDIR(MODE(node)) &&
				!S_ISLNK(MODE(node)))
		{
			ft_pbs("\n%s:\n", node->path);
			print_nodes(node->in);
		}
		node = node->next;
	}
}

void			print_nodes(t_dir *node)
{
	t_dir	*tmp;

	tmp = node;
	if (FLAG_SET(L_FLAG))
		print_longf_nodes(node);
	else
		while (tmp)
		{
			if (FLAG_SET(A_FLAG) || NAME(tmp)[0] != '.')
			{
				if (FLAG_SET(S_FLAG))
					ft_pbs("  %d ", BLOCKS(tmp));
				ft_pbs("%s\t", NAME(tmp));
			}
			tmp = tmp->next;
		}
	write(1, "\n", !FLAG_SET(L_FLAG));
	if (FLAG_SET(RC_FLAG))
		recurse_print(node);
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

	node = new_dir(path, NULL, NULL);
	FLAG_SET(S_FLAG) ? write(1, "1 ", 2) : 0;
	print_permissions(node->stat);
	ft_pbs("@ 1 %s  %s  ", PW_NAME((node)), GR_NAME((node)));
	print_size(node, 0);
	print_date_mod(node);
	ft_putstr(path);
	buff[readlink(node->path, buff, PATH_MAX)] = '\0';
	ft_pbs(" -> %s\n", buff);
	free(node);
}
