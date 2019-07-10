/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:57:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/09 18:34:14 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	init_print_l(t_dir *node, int *offset)
{
	int		this;

	*offset = ft_numlen(node->stat->st_size);
	while ((node = node->next))
	{
		this = ft_numlen(node->stat->st_size);
		if (this > *offset)
			*offset = this;
	}
	*offset += 2;
}

void	print_permissions(t_dir *node)
{
	char			rwx[3];
	unsigned int	permissions;
	int				x;

	ft_putchar(ST_MODE(node, S_IFDIR) ? 'd' : '-'); // ADD MORE TYPES
	permissions = (ST_MODE(node, S_IRWXO) |
					ST_MODE(node, S_IRWXG) |
					ST_MODE(node, S_IRWXU));
	ft_strncpy(rwx, "rwx", 3);
	x = -1;
	while (permissions = (permissions << 1) & 0x3FF, ++x < 9)
		ft_putchar(permissions & 0x200 ? rwx[x % 3] : '-');
}

void	print_links(t_dir *node)
{
	t_dir	*tmp = NULL;
	int		count;

	ft_putstr("  ");
	count = (tmp && ST_MODE(tmp, S_IFDIR) ? 1 : 0);
	if ((tmp = (tmp && ST_MODE(node, S_IFDIR) ? NODE_IN : NULL)))
		while ((tmp = tmp->next))
			if (ST_MODE(tmp, S_IFDIR))
				count++;
	ft_putnbr(count ? count : 1);
}

void	print_size(t_dir *node, int offset)
{
	int		len;
	int		x;

	len = ((x = node->stat->st_size) ? 0 : 1);
	while (x && ++len)
		x /= 10;
	write(1, "          ", offset - len);
	ft_putnbr(node->stat->st_size);
}

void	print_id(t_dir *node)
{
	ft_putchar(' ');
	ft_putstr(getpwuid(node->stat->st_uid)->pw_name);
	ft_putstr("  ");
	ft_putstr(getgrgid(node->stat->st_gid)->gr_name);
}

void	print_date_mod(t_dir *node)
{
	write(1, ctime(&(node->stat->st_mtime)) + 3, 13);
}

void	print_longf_nodes(t_dir *node)
{
	int		offset;

	init_print_l(node, &offset);
	while (node)
	{
		if (node->data->d_name[0] != '.' || FLAG_SET(A_FLAG))
		{
			print_permissions(node);
			print_links(node);
			print_id(node);
			print_size(node, offset);
			print_date_mod(node);
			ft_putchar(' ');
			ft_putstr(node->data->d_name);
			ft_putchar('\n');
		}
		node = node->next;
	}
}
