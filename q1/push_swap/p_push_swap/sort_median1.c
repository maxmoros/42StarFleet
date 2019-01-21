/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_median1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 07:47:11 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 18:46:25 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_triple_a(t_stack *st, int size, int x, int y)
{
	int		median[2];
	int		push[2];
	int		z;

	z = 0;
	triple_init_a(st, size, median, push);
	while (x + y < push[0] + push[1])
		if (st->a[st->i] < median[0])
			x += op_pb(st);
		else if (st->a[st->i] < median[1])
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

static void	sort_triple_b(t_stack *st, int size, int x, int y)
{
	int		median[2];
	int		push[2];
	int		z;

	z = 0;
	triple_init_b(st, size, median, push);
	while (x + y < push[0] + push[1])
		if (st->b[st->j] >= median[0])
			x += op_pa(st);
		else if (st->b[st->j] >= median[1])
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

void		sort_stack_a(t_stack *st, int size, int x, int y)
{
	int		median;
	int		push;

	if (in_order(st, size, 0))
		return ;
	else if (size > 7)
		sort_triple_a(st, size, 0, 0);
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

void		sort_stack_b(t_stack *st, int size, int x, int y)
{
	int		median;
	int		push;

	if (in_order(st, size, 1))
		return ;
	else if (size > 7)
		sort_triple_b(st, size, 0, 0);
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

int			sort_stack(t_stack *st)
{
	sort_stack_a(st, st->size, 0, 0);
	return (in_order(st, st->size, 0) ? 1 : 0);
}
