/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 19:07:56 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 18:38:09 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		init_ops(char op_list[11][4], t_func f[11])
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
	f[4] = op_pb;
	f[5] = op_ra;
	f[6] = op_rb;
	f[7] = op_rr;
	f[8] = op_rra;
	f[9] = op_rrb;
	f[10] = op_rrr;
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
	t_stack		*copy;
	char		**list;
	int			size;

	if (ac == 1)
		return (0);
	list = (ac == 2 ? ft_strsplit(av[1], ' ') : av + 1);
	size = strlist_len(list);
	if (!(stack = build_stack(size)) || !parse_input(stack, list))
		return (free_stack(stack, 0));
	if (!(copy = build_stack(size)) || !parse_input(copy, list))
		return (free_stack(stack, 0) + free_stack(copy, 1));
	sort_stack(stack);
	if (stack->moves > 5)
	{
		clean_ops(stack);
		do_ops(copy, stack->ops_list);
		op_print(copy);
	}
	else
		op_print(stack);
	free_stack(copy, 1);
	free_stack(stack, 1);
	return (0);
}
