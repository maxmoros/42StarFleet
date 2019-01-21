/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 19:25:51 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/03 08:24:09 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		op_ra(t_stack *stack)
{
	int		k;
	int		tmp;

	if (stack->i < 1)
		return (0);
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
	tmp = stack->b[stack->j];
	k = stack->j + 1;
	while (--k > 0)
		stack->b[k] = stack->b[k - 1];
	stack->b[0] = tmp;
	return (1);
}

int		op_rr(t_stack *stack)
{
	return (op_ra(stack) && op_rb(stack));
}
