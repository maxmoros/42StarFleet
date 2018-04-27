/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:40:23 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/22 22:17:21 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		op_rra(t_stack *stack)
{
	int		tmp;
	int		k;

	if (stack->i < 1)
		return (0);
	stack->moves++;
	ft_putstr("rra\n");
	add_op(stack, op_rra);
	tmp = stack->a[0];
	k = -1;
	while (++k < stack->i)
		stack->a[k] = stack->a[k + 1];
	stack->a[stack->i] = tmp;
	return (1);
}

int		op_rrb(t_stack *stack)
{
	int		tmp;
	int		k;

	if (stack->j < 1)
		return (0);
	stack->moves++;
	ft_putstr("rrb\n");
	add_op(stack, op_rrb);
	tmp = stack->b[0];
	k = -1;
	while (++k < stack->j)
		stack->b[k] = stack->b[k + 1];
	stack->b[stack->j] = tmp;
	return (1);
}

int		op_rrr(t_stack *stack)
{
	int		tmp;
	int		k;

	if (stack->i < 1 || stack->j < 1)
		return (0);
	stack->moves++;
	ft_putstr("rrr\n");
	add_op(stack, op_rrr);
	tmp = stack->a[0];
	k = -1;
	while (++k < stack->i)
		stack->a[k] = stack->a[k + 1];
	stack->a[stack->i] = tmp;
	tmp = stack->b[0];
	k = -1;
	while (++k < stack->j)
		stack->b[k] = stack->b[k + 1];
	stack->b[stack->j] = tmp;
	return (1);
}
