/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:21:04 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/03 09:32:43 by mmoros           ###   ########.fr       */
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
	while (++i < 11 && ft_strcmp(op_list[i], op))
		;
	(*count)++;
	if (i < 11)
		return (op_node(next_op(count, op_list, f), f[i]));
	*count = -1;
	return (NULL);
}

void	init_ops(char op_list[11][4], t_func f[11])
{
	ft_strcpy(op_list[0], "sa\0\0");
	ft_strcpy(op_list[1], "sb\0\0");
	ft_strcpy(op_list[2], "ss\0\0");
	ft_strcpy(op_list[3], "pa\0\0");
	ft_strcpy(op_list[4], "pb\0\0");
	ft_strcpy(op_list[5], "ra\0\0");
	ft_strcpy(op_list[6], "rb\0\0");
	ft_strcpy(op_list[7], "rr\0\0");
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

t_ops	*get_ops(int *count)
{
	char	op_list[11][4];
	t_func	f[11];

	init_ops(op_list, f);
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
