/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:57:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/11 21:10:51 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	file_type(blkcnt_t node)
{
	if (S_ISDIR(node))
		return ('d');
	else if (S_ISLNK(node))
		return ('l');
	else if (S_ISBLK(node))
		return ('b');
	else if (S_ISCHR(node))
		return ('c');
	else if (S_ISFIFO(node))
		return ('p');
	else if (S_ISSOCK(node))
		return ('s');
	else
		return ('-');
}

void	print_permissions(struct stat *stat)
{
	char			rwx[3];
	unsigned int	permissions;
	int				x;
	char			c;

	ft_putchar(file_type(stat->st_mode));
	permissions = (ST_MODE(stat, S_IRWXO) | ST_MODE(stat, S_IRWXG) |
					ST_MODE(stat, S_IRWXU));
	ft_strncpy(rwx, "rwx", 3);
	x = -1;
	while (++x < 9)
	{
		permissions = (permissions << 1) & 0x3FF;
		c = rwx[x % 3];
		if (x % 3 == 2)
		{
			if (x & 0x2 && ST_MODE(stat, S_ISUID))
				c = (ST_MODE(stat, S_IXUSR) ? 's' : 'S');
			else if (x & 0x4 && ST_MODE(stat, S_ISGID))
				c = (ST_MODE(stat, S_IXGRP) ? 's' : 'l');
			else if (x & 0x8 && ST_MODE(stat, S_ISVTX))
				c = (ST_MODE(stat, S_IXOTH) ? 't' : 'T');
		}
		ft_putchar(permissions & 0x200 ? c : '-');
	}
}

void	print_links(t_dir *node)
{
	t_dir	*tmp;
	int		count;
	DIR		*dir;

	ft_putstr(S_ISLNK(MODE(node)) ? "@ " : "  ");
	count = 0;
	if (S_ISDIR(MODE(node)))
	{
		if (!node->in)
		{
			dir = opendir(node->path);
			node->in = get_nodes(dir, NULL, 0);
			closedir(dir);
		}
		tmp = node->in;
		while ((tmp = tmp->next))
			if (S_ISDIR(MODE(tmp)))
				count++;
	}
	ft_putnbr(count ? count : 1);
	if (node->in && !FLAG_SET(RC_FLAG))
	{
		free_nodes(node->in);
		node->in = NULL;
	}
}

void	print_size(t_dir *node, int offset)
{
	int		len;
	int		x;

	x = SIZE(node);
	len = (x ? 0 : 1);
	while (x && ++len)
		x /= 10;
	write(1, "          ", offset - len);
	ft_putnbr(SIZE(node));
}
