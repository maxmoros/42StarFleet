/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 07:47:11 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/01 12:03:37 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		median_ab(int *tab, int size, int ab)
{
	int		*set;
	int		tmp;

	if (!(set = (int*)ft_memalloc(sizeof(int) * size)))
		return (0x7FFFFFFF);
	ft_memcpy(set, tab, size * 4);
	ft_qsort(set, size);
	tmp = (ab ? set[size / 2 - (size % 4) / 2] : set[(size + 2) / 4 * 2]);
	free(set);
	return (tmp);
}

int		specific_order(int *tab, int size, int push, int ab)
{
	int		*set;
	int		i;

	if (!(set = (int*)ft_memalloc(sizeof(int) * size)))
		return (0x7FFFFFFF);
	ft_memcpy(set, tab, size * 4);
	ft_qsort(set, size);
	i = -1;
	while (++i < size - push)
		if ((ab && tab[i] != set[i]) || (!ab && tab[i] != set[size - i - 1]))
		{
			free(set);
			return (0);
		}
	free(set);
	return (1);
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

int		sort_stack_a(t_stack *st, int size, int x, int y)
{
	int		median;
	int		push;

	if (in_order(st, size,  0) || ((size == 4 && sort_four(st, 0))))
		return (1);
	else if (size > 3)
	{
		median = median_ab(st->a + st->i - size + 1, size, 0);
		push = (size + 2) / 4 * 2;
		if (specific_order(st->a + st->i - size + 1, size, push, 0))
			return (sort_stack_a(st, push, 0, 0));
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
		return (size == 2 ? op_sa(st) : sort_three_a(st));
	return (1);
}

int		sort_stack_b(t_stack *st, int size, int x, int y)
{
	int		median;
	int		push;

	if (in_order(st, size, 1) || (size == 4 && sort_four(st, 1)))
		return (1);
	else if (size > 2)
	{
		median = median_ab(st->b + st->j - size + 1, size, 1);
		push = (size + 2) / 4 * 2;
		if (specific_order(st->b + st->j - size + 1, size, push, 1))
			return (sort_stack_b(st, push, 0, 0));
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
	return (1);
}

int		sort_stack(t_stack *st)
{
	sort_stack_a(st, st->size, 0, 0);
	return (in_order(st, st->size, 0) ? 1 : 0);
}
