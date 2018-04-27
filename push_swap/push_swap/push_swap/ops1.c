/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:07:16 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/22 21:50:50 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		op_sa(t_stack *stack)
{
	if (stack->i < 1)
		return (0);
	stack->moves++;
	ft_putstr("sa\n");
	add_op(stack, op_sa);
	ft_math_swap(&(stack->a[stack->i]), &(stack->a[stack->i - 1]));
	return (1);
}

int		op_sb(t_stack *stack)
{
	if (stack->j < 1)
		return (0);
	stack->moves++;
	ft_putstr("sb\n");
	add_op(stack, op_sb);
	ft_math_swap(&(stack->b[stack->j]), &(stack->b[stack->j - 1]));
	return (1);
}

int		op_ss(t_stack *stack)
{
	if (stack->i < 1 || stack->j < 1)
		return (0);
	stack->moves++;
	ft_putstr("ss\n");
	add_op(stack, op_ss);
	ft_math_swap(&(stack->a[stack->i]), &(stack->a[stack->i - 1]));
	ft_math_swap(&(stack->b[stack->j]), &(stack->b[stack->j - 1]));
	return (1);
}

int		op_pa(t_stack *stack)
{
	if (stack->j < 0)
		return (0);
	stack->moves++;
	ft_putstr("pa\n");
	add_op(stack, op_pa);
	stack->a[++(stack->i)] = stack->b[stack->j];
	stack->b[stack->j--] = 0;
	return (1);
}

int		op_pb(t_stack *stack)
{
	if (stack->i < 0)
		return (0);
	stack->moves++;
	ft_putstr("pb\n");
	add_op(stack, op_pb);
	stack->b[++(stack->j)] = stack->a[stack->i];
	stack->a[stack->i--] = 0;
	return (1);
}
