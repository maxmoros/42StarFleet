/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:40:23 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/17 19:46:18 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		op_rra(t_stack *stack)
{
	int		tmp;
	int		k;

	if (stack->i < 1)
		return (0);
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
	tmp = stack->b[0];
	k = -1;
	while (++k < stack->j)
		stack->b[k] = stack->b[k + 1];
	stack->b[stack->j] = tmp;
	return (1);
}

int		op_rrr(t_stack *stack)
{
	return (op_rra(stack) && op_rrb(stack));
}
