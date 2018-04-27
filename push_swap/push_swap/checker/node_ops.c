/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:21:04 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/19 13:29:10 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_ops	*op_node(t_ops *next, int (*f)())
{
	t_ops	*node;

	if (!(node = (t_ops*)ft_memalloc(sizeof(t_ops))))
		return (NULL);
	node->next = next;
	node->f = f;
	return (node);
}

t_ops	*next_op(int *count, char op_list[11][4], t_func f[11])
{
	char	*op;
	int		i;

	if (get_next_line(0, &op) < 1 || !*op)
		return (NULL);
	i = -1;
	while (++i < 11 && ft_strcmp(op, op_list[i]))
		;
	(*count)++;
	if (i < 11)
		return (op_node(next_op(count, op_list, f), f[i]));
	*count = -1;
	return (NULL);
}

t_ops	*get_ops(int *count)
{
	char	op_list[11][4] = {"sa\0", "sb\0", "ss\0", "pa\0", "pb\0", "ra\0",
								"rb\0", "rr\0", "rra\0", "rrb\0", "rrr\0"};
	t_func	f[11] = {op_sa, op_sb, op_ss, op_pa, op_pb,
					op_ra, op_rb, op_rr,
					op_rra, op_rrb, op_rrr};

	return (next_op(count, op_list, f));
}

int		do_ops(t_stack *stack, t_ops *ops)
{
	int		out;

	out = 1;
	while (ops)
	{
		if (!ops->f(stack))
			out = 0;
		ops = ops->next;
	}
	return (out);
}
