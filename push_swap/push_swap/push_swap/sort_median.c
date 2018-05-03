/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 07:47:11 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/02 22:16:59 by mmoros           ###   ########.fr       */
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

int		sort_four(t_stack *st, int ab)
{
	if (ab)
	{
		if (st->b[st->j] > st->b[st->j - 2] &&
				st->b[st->j - 2] > st->b[st->j - 1] &&
				st->b[st->j - 1] > st->b[st->j - 3])
			return (op_rb(st) + op_sb(st) + op_rrb(st));
	}
	else
	{
		if (st->a[st->i] < st->a[st->i - 2] &&
				st->a[st->i - 2] < st->a[st->i - 1] &&
				st->a[st->i - 1] < st->a[st->i - 3])
			return (op_ra(st) + op_sa(st) + op_rra(st));
	}
	return (0);
}

void		sort_test_a(t_stack *st, int size, int x, int y, int z)
{
	int		med[2];
	int		push[2];

	med[0] = median_ab(st->a + st->i - size + 1, size, 0, 0);
	push[0] = (size + 2) / 4 * 2;
	med[1] = median_ab(st->a + st->i - size + 1, size, 0, 1);
	push[1] = (size - push[0] + 2) / 4 * 2;
	while (x + y < push[0] + push[1])
		if (st->a[st->i] < med[0])
			x += op_pb(st);
		else if (st->a[st->i] < med[1])
			y += op_pb(st) + op_rb(st) * 0;
		else
			z += op_ra(st);
	while (st->i > size - 1 && z-- && y--)
		op_rrr(st);
	while (y-- > 0)
		op_rrb(st);
	sort_stack_a(st, size - push[0] - push[1], 0, 0);
	sort_stack_b(st, push[1], 0, 0);
	while (push[1]--)
		op_pa(st);
	sort_stack_b(st, push[0], 0, 0);
	while (push[0]--)
		op_pa(st);
}

void		sort_test_b(t_stack *st, int size, int x, int y, int z)
{
	int		med[2];
	int		push[2];

	med[0] = median_ab(st->b + st->j - size + 1, size, 1, 0);
	push[0] = (size + 2) / 4 * 2;
	med[1] = median_ab(st->b + st->j - size + 1, size, 1, 1);
	push[1] = (size - push[0] + 2) / 4 * 2;
	while (x + y < push[0] + push[1])
		if (st->b[st->j] >= med[0])
			x += op_pa(st);
		else if (st->b[st->j] >= med[1])
			y += op_pa(st) + op_ra(st) * 0;
		else
			z += op_rb(st);
	while (st->j > size - 1 && z-- && y--)
		op_rrr(st);
	while (y-- > 0)
		op_rra(st);
	sort_stack_b(st, size - push[0] - push[1], 0, 0);
	sort_stack_a(st, push[1], 0, 0);
	while (push[1]--)
		op_pb(st);
	sort_stack_a(st, push[0], 0, 0);
	while (push[0]--)
		op_pb(st);
}

void	sort_stack_a(t_stack *st, int size, int x, int y)
{
	int		median;
	int		push;

	if (in_order(st, size,  0))
		return ;
	else if (size > 7)
		sort_test_a(st, size, 0, 0, 0);
	else if (size > 3)
	{
		median = median_ab(st->a + st->i - size + 1, size, 0, 0);
		push = (size + 2) / 4 * 2;
		while (x < push)
			if (st->a[st->i] < median)
				x += op_pb(st);
			else
				y += op_ra(st);
		while (st->i > size - 1 && y--)
			op_rra(st);
		sort_stack_a(st, size - push, 0, 0);
		sort_stack_b(st, push, 0, 0);
		while (push-- > 0)
			op_pa(st);
	}
	else
		x = (size == 2 ? op_sa(st) : sort_three_a(st));
}

void	sort_stack_b(t_stack *st, int size, int x, int y)
{
	int		median;
	int		push;

	if (in_order(st, size, 1))
		return ;
	else if (size > 7)
		sort_test_b(st, size, 0, 0, 0);
	else if (size > 2)
	{
		median = median_ab(st->b + st->j - size + 1, size, 1, 0);
		push = (size + 2) / 4 * 2;
		while (x < push)
			if (st->b[st->j] >= median)
				x += op_pa(st);
			else
				y += op_rb(st);
		while (st->j > size && y--)
			op_rrb(st);
		sort_stack_b(st, size - push, 0, 0);
		sort_stack_a(st, push, 0, 0);
		while (push-- > 0)
			op_pb(st);
	}
	else
		op_sb(st);
}

int		sort_stack(t_stack *st)
{
	sort_stack_a(st, st->size, 0, 0);
	return (in_order(st, st->size, 0) ? 1 : 0);
}
