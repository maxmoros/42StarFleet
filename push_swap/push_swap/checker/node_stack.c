/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 20:09:09 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/17 21:19:33 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int			free_stack(t_stack *stack, t_ops *ops, int out)
{
	t_ops	*tmp;

	if (stack)
	{
		if (stack->a)
			free(stack->a);
		if (stack->b)
			free(stack->b);
		free(stack);
	}
	while (ops)
	{
		tmp = ops;
		ops = ops->next;
		free(tmp);
	}
	return (out);
}

t_stack		*build_stack(int size)
{
	t_stack		*stack;

	if (!(stack = (t_stack*)ft_memalloc(sizeof(t_stack))) ||
			!(stack->a = (int*)ft_memalloc(sizeof(int) * size)) ||
			!(stack->b = (int*)ft_memalloc(sizeof(int) * size)))
		return (NULL);
	stack->size = size;
	stack->i = size - 1;
	stack->j = -1;
	return (stack);
}

int			valid_int(char *num)
{
	//NEED TO MAKE CHECK INT LIMITS
	while (*num)
		if ((*num < '0' || *num > '9') && *num != '-' &&
				*num != '+' && *num != ' ')
			return (0);
		else
			num++;
	return (1);
}

int			parse_input(t_stack *stack, char **nums)
{
	int		i;

	i = -1;
	while (++i < stack->size)
		if (!valid_int(nums[i]))
			return (free_stack(stack, NULL, 0));
		else
			stack->a[stack->size - i - 1] = ft_atoi(nums[i]);
	return (1);
}

void		print_stack(t_stack *stack)
{
	int		i;

	ft_putchar('\n');
	i = stack->size;
	while (i--)
	{
		if (i <= stack->i || i < stack->j)
		{
			ft_putchar('\t');
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
