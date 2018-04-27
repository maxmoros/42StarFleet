/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:21:04 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/23 15:09:17 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_ops	*op_node(t_ops *next, int (*f)())
{
	t_ops	*node;

	if (!(node = (t_ops*)ft_memalloc(sizeof(t_ops))))
		return (NULL);
	node->next = next;
	node->f = f;
	return (node);
}

void	add_op(t_stack *stack, int (*f)())
{
	if (stack->ops_list->f)
	{
		stack->op->next = op_node(NULL, f);
		stack->op = stack->op->next;
	}
	else
	{
		stack->ops_list->f = f;
		stack->op = stack->ops_list;
	}
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
	char	op_list[11][4];
	t_func	f[11];

	init_ops(op_list, f);
	return (next_op(count, op_list, f));
}

int		do_ops(t_stack *stack, t_ops *ops)
{
	while (ops)
		if (!ops->f(stack))
			return (0);
		else
		{
			ops = ops->next;
			print_stack(stack);
			delay(500);
		}
	return (1);
}
