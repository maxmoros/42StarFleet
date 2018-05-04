/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:07:16 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/03 08:17:31 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		op_sa(t_stack *stack)
{
	if (stack->i < 1)
		return (0);
	stack->moves++;
	add_op(stack, op_sa, "sa\0\0");
	ft_math_swap(&(stack->a[stack->i]), &(stack->a[stack->i - 1]));
	return (1);
}

int		op_sb(t_stack *stack)
{
	if (stack->j < 1)
		return (0);
	stack->moves++;
	add_op(stack, op_sb, "sb\0\0");
	ft_math_swap(&(stack->b[stack->j]), &(stack->b[stack->j - 1]));
	return (1);
}

int		op_ss(t_stack *stack)
{
	if (stack->i < 1 || stack->j < 1)
		return (0);
	stack->moves++;
	add_op(stack, op_ss, "ss\0\0");
	ft_math_swap(&(stack->a[stack->i]), &(stack->a[stack->i - 1]));
	ft_math_swap(&(stack->b[stack->j]), &(stack->b[stack->j - 1]));
	return (1);
}

int		op_pa(t_stack *stack)
{
	if (stack->j < 0)
		return (0);
	stack->moves++;
	add_op(stack, op_pa, "pa\0\0");
	stack->a[++(stack->i)] = stack->b[stack->j];
	stack->b[stack->j--] = 0;
	return (1);
}

int		op_pb(t_stack *stack)
{
	if (stack->i < 0)
		return (0);
	stack->moves++;
	add_op(stack, op_pb, "pb\0\0");
	stack->b[++(stack->j)] = stack->a[stack->i];
	stack->a[stack->i--] = 0;
	return (1);
}
