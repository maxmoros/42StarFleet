/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/10 11:57:14 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	recurse_print(t_dir *node)
{
	while (node)
	{
		if (!(FLAG_SET(A_FLAG) ^ (node->data->d_name[0] == '.')) &&
				CMP_DIR(".") && CMP_DIR("..") && node->stat->st_mode & S_IFDIR)
		{
			ft_putstr("\n");
			ft_putstr(node->path);
			ft_putstr(":\n");
			print_nodes(node->in);
		}
		node = node->next;
	}
}

void	print_nodes(t_dir *node)
{
	t_dir	*tmp;

	tmp = node;
	if (FLAG_SET(L_FLAG))
		print_longf_nodes(node);
	else
		while (tmp)
		{
			if (FLAG_SET(A_FLAG) || tmp->data->d_name[0] != '.')
			{
				ft_putstr(tmp->data->d_name);
				ft_putchar('\t');
			}
			tmp = tmp->next;
		}
	write(1, "\n", !FLAG_SET(L_FLAG));
	if (FLAG_SET(RC_FLAG))
		recurse_print(node);
}
