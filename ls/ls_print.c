/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:54:01 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/05 13:20:22 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_nodes(t_dir *node, char flags)
{
	t_dir	*tmp;

	tmp = node;
	while (tmp)
	{
		if (flags & A_FLAG || tmp->data->d_name[0] != '.')
		{
			ft_putstr(tmp->data->d_name);
			ft_putchar('\n');
		}
		tmp = tmp->next;
	}
}