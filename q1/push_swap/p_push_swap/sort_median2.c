/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_median2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 22:20:43 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 16:34:35 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		median_ab(int *tab, int size, int ab, int sub_med)
{
	int		*set;
	int		tmp;

	if (!(set = (int*)ft_memalloc(sizeof(int) * size)))
		return (0x7FFFFFFF);
	ft_memcpy(set, tab, size * 4);
	ft_qsort(set, size);
	tmp = (ab ? size / 2 - (size % 4) / 2 : (size + 2) / 4 * 2);
	if (sub_med)
		tmp = (ab ? median_ab(set, tmp, 1, 0) :
				median_ab(set + tmp, size - tmp, 0, 0));
	else
		tmp = set[tmp];
	free(set);
	return (tmp);
}

int		sort_three_a(t_stack *st)
{
	int		tmp;

	if (st->a[2] < st->a[1])
	{
		if (st->a[0] < st->a[1])
			tmp = (st->a[0] < st->a[2] ? op_rra(st) : op_rra(st) + op_sa(st));
	}
	else if (st->a[1] < st->a[0])
		tmp = (st->a[0] < st->a[2] ? op_ra(st) : op_sa(st));
	else
		tmp = op_sa(st) + op_rra(st);
	return (1);
}

void	triple_init_a(t_stack *st, int size, int median[2], int push[2])
{
	median[0] = median_ab(st->a + st->i - size + 1, size, 0, 0);
	push[0] = (size + 2) / 4 * 2;
	median[1] = median_ab(st->a + st->i - size + 1, size, 0, 1);
	push[1] = (size - push[0] + 2) / 4 * 2;
}

void	triple_init_b(t_stack *st, int size, int median[2], int push[2])
{
	median[0] = median_ab(st->b + st->j - size + 1, size, 1, 0);
	push[0] = (size + 2) / 4 * 2;
	median[1] = median_ab(st->b + st->j - size + 1, size, 1, 1);
	push[1] = (size - push[0] + 2) / 4 * 2;
}
