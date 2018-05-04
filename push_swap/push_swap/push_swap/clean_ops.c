/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:56:18 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/02 23:05:50 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	op_match(t_ops *node, char *str)
{
	t_ops	*tmp;
	int		len;

	if (!node)
		return (0);
	tmp = node->next;
	while (tmp && *str)
	{
		len = ft_strlen(tmp->op);
		if (ft_strncmp(tmp->op, str, len))
			return (0);
		str += 1 + len;
		tmp = tmp->next;
	}
	if (*str)
		return (0);
	return (1);
}

static int	opposite(t_stack *stack, int del)
{
	t_ops	*node;
	t_ops	*tmp;

	node = stack->ops_list;
	while (node && (tmp = node->next) && tmp->next)
		if (op_match(node, "pa pb ") || op_match(node, "pb pa ") ||
				op_match(node, "ra rra ") || op_match(node, "rb rrb ") ||
				op_match(node, "rra ra ") || op_match(node, "rrb rb "))
		{
			node->next = node->next->next->next;
			free(tmp->next->op);
			free(tmp->next);
			free(tmp->op);
			free(tmp);
			del += 2;
		}
		else
			node = node->next;
	stack->moves -= del;
	return (del);
}

static int	ss_rr_rrr(t_stack *stack, int del)
{
	t_ops	*node;
	t_ops	*tmp;

	node = stack->ops_list;
	while (node && (tmp = node->next) && tmp->next)
		if (op_match(node, "sa sb ") || op_match(node, "sb sa ") ||
				op_match(node, "ra rb ") || op_match(node, "rb ra ") ||
				op_match(node, "rra rrb ") || op_match(node, "rrb rra "))
		{
			node->next = node->next->next;
			if (node->next->f == op_sb || node->next->f == op_sa)
				node->next->f = op_ss;
			else if (node->next->f == op_rb || node->next->f == op_ra)
				node->next->f = op_rr;
			else
				node->next->f = op_rrr;
			free(tmp->op);
			free(tmp);
			del += 1;
		}
		else
			node = node->next;
	stack->moves -= del;
	return (del);
}

int			clean_ops(t_stack *stack)
{
	if (stack->ops_list->f && stack->ops_list->next->f)
		return (opposite(stack, 0) || ss_rr_rrr(stack, 0));
	else
		return (0);
}
