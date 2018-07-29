/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:07:16 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/03 08:17:06 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		op_sa(t_stack *stack)
{
	if (stack->i < 1)
		return (0);
	ft_math_swap(&(stack->a[stack->i]), &(stack->a[stack->i - 1]));
	return (1);
}

int		op_sb(t_stack *stack)
{
	if (stack->j < 1)
		return (0);
	ft_math_swap(&(stack->b[stack->j]), &(stack->b[stack->j - 1]));
	return (1);
}

int		op_ss(t_stack *stack)
{
	return (op_sa(stack) && op_sb(stack));
}

int		op_pa(t_stack *stack)
{
	if (stack->j < 0)
		return (0);
	stack->a[++(stack->i)] = stack->b[stack->j];
	stack->b[stack->j--] = 0;
	return (1);
}

int		op_pb(t_stack *stack)
{
	if (stack->i < 0)
		return (0);
	stack->b[++(stack->j)] = stack->a[stack->i];
	stack->a[stack->i--] = 0;
	return (1);
}
