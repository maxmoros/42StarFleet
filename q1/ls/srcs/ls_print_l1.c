/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:57:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/12 14:45:02 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	init_print_l(t_dir *node, int *offset, int *blck_len, uint32_t blck_sum)
{
	int			this;
	uint8_t		exists;

	*offset = 0;
	exists = (FLAG_SET(A_FLAG) || node->next->next ? 1 : 0);
	while (node)
	{
		if (FLAG_SET(A_FLAG) || (!(NAME(node)[0] == '.') &&
				CMP_DIR(".") && CMP_DIR("..")))
		{
			this = ft_numlen(SIZE(node));
			if (this > *offset)
				*offset = this;
			blck_sum += BLOCKS(node);
			if (BLOCKS(node) > *blck_len)
				*blck_len = BLOCKS(node);
		}
		node = node->next;
	}
	exists ? ft_pbs("total %d\n", blck_sum) : 0;
	this = *blck_len;
	*blck_len = 1;
	while (this /= 10)
		(*blck_len)++;
}

void	print_date_mod(t_dir *node)
{
	write(1, CTIME(node) + 3, 8);
	if (ft_strncmp(CTIME(node) + 20, "2019", 4))
		write(1, CTIME(node) + 19, 5);
	else
		write(1, CTIME(node) + 11, 5);
	ft_putchar(' ');
	ft_putstr(NAME(node));
}

void	print_blocks(t_dir *node, int blck_len)
{
	if (CMP_DIR(".") && CMP_DIR(".."))
	{
		write(1, "            ", blck_len - ft_numlen(BLOCKS(node)));
		ft_putnbr(BLOCKS(node));
	}
	else
	{
		write(1, "            ", blck_len - 1);
		write(1, "0", 1);
	}
	write(1, " ", 1);
}

void	print_links(t_dir *node)
{
	t_dir	*tmp;
	int		count;
	DIR		*dir;

	ft_putstr(S_ISLNK(MODE(node)) ? "@ " : "  ");
	count = 0;
	if (S_ISDIR(MODE(node)) && (dir = opendir(node->path)))
	{
		node->in = get_nodes(dir, node, 0);
		closedir(dir);
		tmp = node->in;
		while (tmp)
		{
			count++;
			tmp = tmp->next;
		}
	}
	ft_putnbr(count ? count : 1);
	if (node->in && !FLAG_SET(RC_FLAG))
	{
		free_nodes(node->in);
		node->in = NULL;
	}
}

void	print_longf_nodes(t_dir *node)
{
	int		offset;
	int		blck_len;
	char	buff[PATH_MAX + 1];

	blck_len = 0;
	init_print_l(node, &offset, &blck_len, 0);
	while (node)
	{
		if (NAME(node)[0] != '.' || FLAG_SET(A_FLAG))
		{
			FLAG_SET(S_FLAG) ? print_blocks(node, blck_len) : 0;
			print_permissions(node->stat);
			print_links(node);
			print_id(node);
			print_size(node, offset + 2);
			print_date_mod(node);
			if (S_ISLNK(MODE(node)))
			{
				buff[readlink(node->path, buff, PATH_MAX)] = '\0';
				ft_pbs(" -> %s", buff);
			}
			ft_putchar('\n');
		}
		node = node->next;
	}
}
