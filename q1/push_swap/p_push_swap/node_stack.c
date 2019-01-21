/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:09:09 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/29 17:18:00 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			in_order(t_stack *st, int size, int ab)
{
	if (ab)
	{
		while (--size > 0)
			if (st->b[st->j - size] > st->b[st->j - size + 1])
				return (0);
	}
	else
		while (--size > 0)
			if (st->a[st->i - size] < st->a[st->i - size + 1])
				return (0);
	return (1);
}

int			free_stack(t_stack *stack, int out)
{
	t_ops	*ops;
	t_ops	*tmp;

	ops = stack->ops_list;
	while (ops)
	{
		tmp = ops;
		ops = ops->next;
		if (tmp->op)
			free(tmp->op);
		free(tmp);
	}
	if (stack)
	{
		if (stack->a)
			free(stack->a);
		if (stack->b)
			free(stack->b);
		free(stack);
	}
	if (!out)
		ft_putstr("Error\n");
	return (out);
}

t_stack		*build_stack(int size)
{
	t_stack		*stack;

	if (!(stack = (t_stack*)ft_memalloc(sizeof(t_stack))) ||
			!(stack->ops_list = op_node(NULL, NULL, NULL)) ||
			!(stack->a = (int*)ft_memalloc(sizeof(int) * size)) ||
			!(stack->b = (int*)ft_memalloc(sizeof(int) * size)))
		return (NULL);
	stack->op = stack->ops_list;
	stack->size = size;
	stack->moves = 0;
	stack->i = size - 1;
	stack->j = -1;
	return (stack);
}

int			parse_input(t_stack *stack, char **nums)
{
	int		i;
	int		j;
	int		tmp;

	i = -1;
	while (++i < stack->size)
		if (!ft_isint(nums[i]))
			return (0);
		else
		{
			tmp = stack->size - i - 1;
			stack->a[tmp] = ft_atoi(nums[i]);
			j = tmp;
			while (++j < stack->size)
				if (stack->a[tmp] == stack->a[j])
					return (0);
		}
	return (1);
}

void		print_stack(t_stack *stack)
{
	int		i;

	ft_putchar('\n');
	i = stack->size;
	while (i--)
	{
		if (stack->i >= i || stack->j >= i)
		{
			ft_putstr("\t");
			if (i <= stack->i)
				ft_putnbr(stack->a[i]);
			ft_putchar('\t');
			if (i <= stack->j)
				ft_putnbr(stack->b[i]);
			ft_putchar('\n');
		}
	}
	ft_putstr("\n\tA\tB\n\n");
}
