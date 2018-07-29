/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:07:56 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 17:31:09 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			in_order(t_stack *stack)
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

static int	strlist_len(char **list)
{
	int		count;

	count = 0;
	while (*list++)
		count++;
	return (count);
}

int			main(int ac, char **av)
{
	t_stack		*stack;
	t_ops		*ops;
	int			count;
	char		**list;
	int			size;

	if (ac == 1)
		return (0);
	list = (ac == 2 ? ft_strsplit(av[1], ' ') : av + 1);
	size = strlist_len(list);
	if (!(stack = build_stack(size)) || (!parse_input(stack, list)))
		return (free_stack(stack, NULL, 0));
	count = 0;
	if (!(ops = get_ops(&count)) && !in_order(stack))
		return (free_stack(stack, NULL, 0));
	if (count < 0)
		return (free_stack(stack, ops, 0));
	do_ops(stack, ops);
	if (in_order(stack))
		ft_putstr("OK\n");
	else
		ft_putstr("KO\n");
	free_stack(stack, ops, 1);
	return (0);
}
