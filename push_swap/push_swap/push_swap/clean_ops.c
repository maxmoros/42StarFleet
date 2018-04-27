/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 10:56:18 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/22 22:17:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_ops	*itop(t_ops *ops, int count)
{
	t_ops	*node;

	node = ops;
	while (count--)
		node = node->next;
	return (node);
}

int		pa_pb(t_stack *stack, int del)
{
	t_ops	*node;
	t_ops	*tmp;

	node = stack->ops_list;
	while (node && (tmp = node->next) && tmp->next)
		if ((tmp->f == op_pa && tmp->next->f == op_pb) ||
				(tmp->f == op_ra && tmp->next->f == op_rra) ||
				(tmp->f == op_rb && tmp->next->f == op_rrb) ||
				(tmp->f == op_rra && tmp->next->f == op_ra) ||
				(tmp->f == op_rrb && tmp->next->f == op_rb) ||
			(tmp->f == op_pb && tmp->next->f == op_pa))
		{
			node->next = node->next->next->next;
			free(tmp->next);
			free(tmp);
			del += 2;
		}
		else
			node = node->next;
	stack->moves -= del;
	return (del);
}

int		pp_s_pp(t_stack *stack, int del)
{
	t_ops	*node;
	t_ops	*tmp;

	node = stack->ops_list;
	while (node && (tmp = node->next) && tmp->next && tmp->next->next &&
			tmp->next->next->next && tmp->next->next->next->next)
		if ((tmp->f == op_pa && tmp->next->f == op_pa &&
				tmp->next->next->f == op_sa && tmp->next->next->next->f == op_pb
				&& tmp->next->next->next->next->f == op_pb) || (tmp->f == op_pb
				&& tmp->next->f == op_pb && tmp->next->next->f == op_sb &&
				tmp->next->next->next->f == op_pa &&
				tmp->next->next->next->next->f == op_pa))
		{
			node->next = node->next->next->next->next->next;
			node->next->f = (node->next->f == op_pb ? op_sb : op_sa);
			free(tmp->next->next->next);
			free(tmp->next->next);
			free(tmp->next);
			free(tmp);
			del += 4;
		}
		else
			node = node->next;
	stack->moves -= del;
	return (del);
}

int		ss_rr_rrr(t_stack *stack, int del)
{
	t_ops	*node;
	t_ops	*tmp;

	node = stack->ops_list;
	while (node && (tmp = node->next) && tmp->next)
		if ((tmp->f == op_sa && tmp->next->f == op_sb) ||
			(tmp->f == op_sb && tmp->next->f == op_sa) ||
			(tmp->f == op_ra && tmp->next->f == op_rb) ||
			(tmp->f == op_rb && tmp->next->f == op_ra) ||
			(tmp->f == op_rra && tmp->next->f == op_rrb) ||
			(tmp->f == op_rrb && tmp->next->f == op_rra))
		{
			node->next = node->next->next;
			if (node->next->f == op_sb || node->next->f == op_sa)
				node->next->f = op_ss;
			else if (node->next->f == op_rb || node->next->f == op_ra)
				node->next->f = op_rr;
			else 
				node->next->f = op_rrr;
			free(tmp);
			del += 1;
		}
		else
			node = node->next;
	stack->moves -= del;
	return (del);
}

int		four_mid_switch(t_stack *stack, int del, t_ops *node, t_ops *tmp)
{
	node = stack->ops_list;
	while (node && (tmp = node->next) && itop(node, 2) && itop(node, 3) &&
			itop(node, 4) && itop(node, 5) && itop(node, 6) && itop(node, 7))
		if ((itop(node, 1)->f == op_pb && itop(node, 2)->f == op_ra &&
				itop(node, 3)->f == op_pb && itop(node, 4)->f == op_rra &&
				itop(node, 5)->f == op_sb && itop(node, 6)->f == op_pa &&
				itop(node, 7)->f == op_pa) || (itop(node, 1)->f == op_pa &&
				itop(node, 2)->f == op_rb && itop(node, 3)->f == op_pa &&
				itop(node, 4)->f == op_rrb && itop(node, 5)->f == op_sa &&
				itop(node, 6)->f == op_pb && itop(node, 7)->f == op_pb))
		{
			node->next = itop(node, 5);
			node->next->f = (node->next->f == op_sb ? op_ra : op_rb);
			itop(node, 2)->f = (itop(node, 2)->f == op_pa ? op_sa : op_sb);
			itop(node, 3)->f = (itop(node, 3)->f == op_pa ? op_rra : op_rrb);
			free(itop(tmp, 3));
			free(itop(tmp, 2));
			free(itop(tmp, 1));
			free(tmp);
			del += 4;
		}
		else
			node = node->next;
	stack->moves -= del;
	return (del);
}

int		clean_ops(t_stack *stack)
{
	if (stack->ops_list->f && stack->ops_list->next->f)
		return (pp_s_pp(stack, 0) + pa_pb(stack, 0) + ss_rr_rrr(stack, 0));
	else
		return (0);
}
