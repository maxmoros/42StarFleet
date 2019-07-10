/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/09 19:01:04 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	recurse_print(t_dir *node)
{
	while (node)
	{
	//	printf("HERE1 [%s] \'%s\'\n", (node->up ? node->up->data->d_name : "root"), node->data->d_name);
		if (CMP_DIR(".") && CMP_DIR("..") &&
			!(FLAG_SET(A_FLAG) ^ (node->data->d_name[0] == '.')))
		{
			if (node->stat->st_mode & S_IFDIR)
			{
				ft_putstr("\n");
				ft_putstr(node->path);
				ft_putstr(":\n");
	//			printf("  HERE2 NODE_IN? \'%s\'\n", node->in ? "yes" : "no");
				if (node->in)
	//				printf("    HERE3 \'%s\'\n", node->in->data->d_name);
				print_nodes(node->in);
			}
		}
		node = node->next;
	}
//	printf("\033[33;5;205mOUT\033[m\n");
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
	write(1, "\n", 1);
	if (FLAG_SET(RC_FLAG))
		recurse_print(node);
}
