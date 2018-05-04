/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:07:56 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/02 22:56:17 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		in_order(t_stack *stack)
{
	int		k;

	if (stack->j > -1)
		return (0);
	k = stack->i + 1;
	while (--k > 0)
		if (stack->a[k] > stack->a[k - 1])
			return (0);
	return (1);
}

int		main(int ac, char **av)
{
	t_stack		*stack;
	t_ops		*ops;
	int			count;

	if (ac > 1)
	{
		if (!(stack = build_stack(ac - 1)))
			return (free_stack(stack, NULL, 0));
		if (!parse_input(stack, av + 1))
			return (free_stack(stack, NULL, 0));
		count = 0;
		if (!(ops = get_ops(&count)))
			return (free_stack(stack, NULL, 0));
		if (count < 0)
			return (free_stack(stack, ops, 0));
		do_ops(stack, ops);
		if (in_order(stack))
			ft_putstr("OK\n");
		else
			ft_putstr("KO\n");
	}
	return (0);
}
