/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/05 21:52:11 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	recurse_print(t_dir *node, char flags)
{
	while (node)
	{
		if (ft_strcmp(node->data->d_name, ".") &&
			ft_strcmp(node->data->d_name, ".."))
		{
			if (node->stat->st_mode & S_IFDIR)
			{
				ft_putstr("\n\n./");
				ft_putstr(node->path);
				ft_putstr(":\n");
				print_nodes(node->in, flags);
			}
		}
		node = node->next;
	}
}

void	print_permissions(t_dir *node)
{
	char			rwx[3];
	unsigned int	permissions;
	int				x;

	permissions = (node->stat->st_mode & S_IRWXO) |
					((node->stat->st_mode & S_IRWXG)) |
					((node->stat->st_mode & S_IRWXU));
	ft_strncpy(rwx, "rwx", 3);
	x = -1;
	if (node->stat->st_mode & S_IFDIR)
		ft_putchar('d');
	else
		ft_putchar('-');
	while (++x < 9)
	{
		if (permissions / 0xFF)
			ft_putchar(rwx[x % 3]);
		else
			ft_putchar('-');
		permissions = (permissions << 1) & 0x1FF;
	}
}

void	print_links(t_dir *node)
{
	t_dir	*tmp;
	int		count;

	ft_putstr("  ");
	if (!(node->stat->st_mode & S_IFDIR))
	{
		ft_putchar('1');
		return ;
	}
	tmp = node->in;
	count = 2;
	while (tmp)
	{
		if (tmp->stat->st_mode & S_IFDIR)
			count++;
		tmp = tmp->next;
	}
	ft_putnbr(count);
}

void	print_ugid(t_dir *node)
{
	struct passwd	*pwd;
	struct group	*grp;

	pwd = getpwuid(node->stat->st_uid);
	grp = getgrgid(node->stat->st_gid);

	ft_putchar(' ');
	ft_putstr(pwd->pw_name);
	ft_putstr("  ");
	ft_putstr(grp->gr_name);
}

void	print_size(t_dir *node)
{
	int		count;
	int		x;

	count = 0;
	x = node->stat->st_size;
	while (x && ++count)
		x /= 10;
	write(1, "          ", 10 - count);
	ft_putnbr(node->stat->st_size);
}

void	print_longf_nodes(t_dir *node, char flags)
{
	while (node)
	{
		if (node->data->d_name[0] != '.' || flags & A_FLAG)
		{
			print_permissions(node);
			print_links(node);
			print_ugid(node);
			print_size(node);
			ft_putchar(' ');
			ft_putstr(node->data->d_name);
			ft_putchar('\n');
		}
		node = node->next;
	}
	flags &= 0xFF;
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
