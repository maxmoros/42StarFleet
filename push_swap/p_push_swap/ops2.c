/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:25:51 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 16:34:42 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_print(t_stack *stack)
{
	t_ops	*node;

	node = stack->ops_list;
	while (node && ft_strlen(node->op))
	{
		ft_putstr(node->op);
		ft_putchar('\n');
		node = node->next;
	}
}

int		op_ra(t_stack *stack)
{
	int		k;
	int		tmp;

	if (stack->i < 1)
		return (0);
	stack->moves++;
	add_op(stack, op_ra, "ra\0\0");
	tmp = stack->a[stack->i];
	k = stack->i + 1;
	while (--k > 0)
		stack->a[k] = stack->a[k - 1];
	stack->a[0] = tmp;
	return (1);
}

int		op_rb(t_stack *stack)
{
	int		k;
	int		tmp;

	if (stack->j < 1)
		return (0);
	stack->moves++;
	add_op(stack, op_rb, "rb\0\0");
	tmp = stack->b[stack->j];
	k = stack->j + 1;
	while (--k > 0)
		stack->b[k] = stack->b[k - 1];
	stack->b[0] = tmp;
	return (1);
}

int		op_rr(t_stack *stack)
{
	int		k;
	int		tmp;

	if (stack->j < 1 || stack->i < 1)
		return (0);
	stack->moves++;
	add_op(stack, op_rr, "rr\0\0");
	tmp = stack->a[stack->i];
	k = stack->i + 1;
	while (--k > 0)
		stack->a[k] = stack->a[k - 1];
	stack->a[0] = tmp;
	tmp = stack->b[stack->j];
	k = stack->j + 1;
	while (--k > 0)
		stack->b[k] = stack->b[k - 1];
	stack->b[0] = tmp;
	return (1);
}
