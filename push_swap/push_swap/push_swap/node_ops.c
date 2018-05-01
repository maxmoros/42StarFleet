/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:21:04 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/01 10:23:04 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_ops	*op_node(t_ops *next, int (*f)(), char *op)
{
	t_ops	*node;

	if (!(node = (t_ops*)ft_memalloc(sizeof(t_ops))) ||
			!(node->op = (char*)ft_memalloc(sizeof(char) * 4)))
		return (NULL);
	node->next = next;
	node->f = f;
	if (op)
		ft_strncpy(node->op, op, 4);
	return (node);
}

void	add_op(t_stack *stack, int (*f)(), char *op)
{
	if (stack->ops_list->f)
	{
		stack->op->next = op_node(NULL, f, op);
		stack->op = stack->op->next;
	}
	else
	{
		stack->ops_list->f = f;
		ft_strncpy(stack->ops_list->op, op, 4);
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
		return (op_node(next_op(count, op_list, f), f[i], &op_list[i][0]));
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
	//		print_stack(stack);
	//		delay(200);
		}
	return (1);
}
