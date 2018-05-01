/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:07:56 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/01 11:51:37 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

void	init_ops(char op_list[11][4], t_func f[11])
{
	ft_strcpy(op_list[0], "sa\0");
	ft_strcpy(op_list[1], "sb\0");
	ft_strcpy(op_list[2], "ss\0");
	ft_strcpy(op_list[3], "pa\0");
	ft_strcpy(op_list[4], "pb\0");
	ft_strcpy(op_list[5], "ra\0");
	ft_strcpy(op_list[6], "rb\0");
	ft_strcpy(op_list[7], "rr\0");
	ft_strcpy(op_list[8], "rra\0");
	ft_strcpy(op_list[9], "rrb\0");
	ft_strcpy(op_list[10], "rrr\0");
	f[0] = op_sa;
	f[1] = op_sb;
	f[2] = op_ss;
	f[3] = op_pa;
	f[4] = op_pa;
	f[5] = op_ra;
	f[6] = op_rb;
	f[7] = op_rr;
	f[8] = op_rra;
	f[9] = op_rrb;
	f[10] = op_rrr;
}

int		main(int ac, char **av)
{
	t_stack		*stack;
	t_stack		*copy;

	if (ac > 1)
	{
		if (!(stack = build_stack(ac - 1)) ||
				!parse_input(stack, av + 1))
			return (free_stack(stack, 0));
		if (!(copy = build_stack(ac - 1)) ||
				!parse_input(copy, av + 1))
			return (free_stack(stack, 0) + free_stack(copy, 0));
		if (sort_stack(stack))
			ft_putstr("\nOK!\n");
		else
			ft_putstr("\nKO!\n");
		ft_putstr("\nfinished in ");
		ft_putnbr(stack->moves);
		ft_putstr("steps\n");
		if (stack->moves)
		{
			while (clean_ops(stack))
				;
			do_ops(copy, stack->ops_list);
	//		op_print(copy);
			if (in_order(copy, copy->size, 0))
				ft_putstr("\nOK!\n");
			else
				ft_putstr("\nKO!\n");
			ft_putstr("\nfinished in ");
			ft_putnbr(copy->moves);
			ft_putstr("steps\n");
		}
		free_stack(stack, 0);
		free_stack(copy, 0);
	}
	return (0);
}
