/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:57:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/10 16:01:21 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"


void	init_print_l(t_dir *node, int *offset, int *blck_len, uint32_t blck_sum)
{
	int			this;

	*offset = 0;
	while (node ? (this = ft_numlen(node->stat->st_size)) : 0, node)
	{
		if (this > *offset)
			*offset = this;
		if (!(FLAG_SET(A_FLAG) ^ (node->data->d_name[0] == '.')) &&
				CMP_DIR(".") && CMP_DIR(".."))
		{
			blck_sum += node->stat->st_blocks;
			if (node->stat->st_blocks > *blck_len)
				*blck_len = node->stat->st_blocks;
		}
		node = node->next;
	}
	ft_putstr("total ");
	ft_putnbr(blck_sum);
	write(1, "\n", 1);
	this = *blck_len;
	*blck_len = 0;
	while ((*blck_len)++, this /= 10)
		;
}

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

void	print_permissions(t_dir *node)
{
	char			rwx[3];
	unsigned int	permissions;
	int				x;
	char			c;

	ft_putchar(file_type(node->stat->st_mode));
	permissions = (ST_MODE(node, S_IRWXO) | ST_MODE(node, S_IRWXG) |
					ST_MODE(node, S_IRWXU));
	ft_strncpy(rwx, "rwx", 3);
	x = -1;
	while (permissions = (permissions << 1) & 0x3FF, ++x < 9)
	{
		c = '-';
		if (x % 3 == 2)
		{
			if (x & 0x2 && ST_MODE(node, S_ISUID))
				c = (ST_MODE(node, S_IXUSR) ? 's' : 'S');
			else if (x & 0x4 && ST_MODE(node, S_ISGID))
				c = (ST_MODE(node, S_IXGRP) ? 's' : 'l');
			else if (x & 0x8 && ST_MODE(node, S_ISVTX))
				c = (ST_MODE(node, S_IXOTH) ? 't' : 'T');
		}
		ft_putchar(permissions & 0x200 ? rwx[x % 3] : c);
	}
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

void	print_id(t_dir *node)
{
	struct passwd	*uid;
	struct group	*gid;

	ft_putchar(' ');
	ft_putstr((uid = getpwuid(node->stat->st_uid)) ? uid->pw_name : NULL);
	ft_putstr("  ");
	ft_putstr((gid = getgrgid(node->stat->st_gid)) ? gid->gr_name : NULL);
}

void	print_size(t_dir *node, int offset)
{
	int		len;
	int		x;

	print_permissions(node);
	print_links(node);
	print_id(node);
	len = ((x = node->stat->st_size) ? 0 : 1);
	while (x && ++len)
		x /= 10;
	write(1, "          ", offset - len);
	ft_putnbr(node->stat->st_size);
}

void	print_date_mod(t_dir *node)
{
	write(1, ctime(&(node->stat->st_mtime)) + 3, 8);
	if (ft_strncmp(ctime(&(node->stat->st_mtime)) + 20, "2019", 4))
		write(1, ctime(&(node->stat->st_mtime)) + 19, 5);
	else
		write(1, ctime(&(node->stat->st_mtime)) + 11, 5);
	ft_putchar(' ');
}

void	print_blocks(t_dir *node, int blck_len)
{	
	if (CMP_DIR(".") && CMP_DIR(".."))
	{
		write(1, "            ", blck_len - ft_numlen(node->stat->st_blocks));
		ft_putnbr(node->stat->st_blocks);
	}
	else
	{
		write(1, "            ", blck_len - 1);
		write(1, "0", 1);
	}
	write(1, " ", 1);
}

void	print_longf_nodes(t_dir *node)
{
	int		offset;
	int		blck_len;
	int		x;
	char	buff[PATH_MAX + 1];

	init_print_l(node, &offset, &blck_len, 0);
	while (node)
	{
		if (node->data->d_name[0] != '.' || FLAG_SET(A_FLAG))
		{
			FLAG_SET(S_FLAG) ? print_blocks(node, blck_len) : 0;
			print_size(node, offset + 2);
			print_date_mod(node);
			ft_putstr(node->data->d_name);
			if (S_ISLNK(node->stat->st_mode))
			{
				x = readlink(node->path, buff, PATH_MAX);
				buff[x] = '\0';
				ft_putstr(" -> ");
				ft_putstr(buff);
			}
			ft_putchar('\n');
		}
		node = node->next;
	}
}
