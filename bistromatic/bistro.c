/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bistro.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 19:19:28 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/09 09:19:48 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

void	clean_digits(char *equ, char *base_chars)
{
	int		base;
	int		i;
	int		j;
	int		swap;

	base = ft_strlen(base_chars);
	i = -1;
	while (equ[++i])
	{
		j = -1;
		swap = 1;
		while (++j < base && swap)
			if (equ[i] == base_chars[j])
			{
				equ[i] = 'a' + j;
				swap = 0;
			}
	}
}

void	print_tree(t_equ *start)
{
	if (start->left)
	{
		if (start->up)
			ft_putchar('(');
		print_tree(start->left);
	}
	if (start->op)
		ft_putchar(start->op);
	else if (start->value)
	if (start->right)
	{
		print_tree(start->right);
		if (start->up)
			ft_putchar(')');
	}
	if (!start->op && !start->value && start->up)
		ft_putchar(')');
}

void	print_num(t_num *num)
{
	int	i;
	int j;
	
	i = (num->ldig % num->cut ? num->ldig / num->cut + 1 :
		   	num->ldig / num->cut);
	i = (i ? i : 1);	
	j = -1;
	while (++j < i)
		ft_putnbr(num->left[j]);
	if (num->rdig)
	{
		ft_putchar('.');
		i = (num->rdig % num->cut ? num->rdig / num->cut + 1 :
		   	num->rdig / num->cut);
		i = (i ? i : 1);
		j = -1;
		while (++j < i)
			ft_putnbr(num->right[j]);
	}
}

int		main(int ac, char **av)
{
	char	*input;
//	t_equ	*start;
	int		**mtab;
	int		i;
	t_num	*test;

	mtab = (int**)malloc(sizeof(int*) * 10000);
	i = -1;
	while (++i < 10000)
		mtab[i] = (int*)malloc(sizeof(int) * 10000);

	if (ac == 3)
	{
		ft_putstr("Enter a single number base 2-16. *can use float*:\n");
		get_next_line(0, &input);
		clean_digits(input, av[1]);
		test = new_num(&input, ft_strlen(av[1]));
		print_num(test);
	/*
		ft_putstr("\n\nEnter an Equation:");
		get_next_line(0, &input);
		clean_digits(input, av[1]);
		ft_putstr("\n");
		if(!(start = equ_home(NULL, &input, ft_strlen(av[1]))))
		{
			ft_putstr("parse error");
			return (0);
		}
		ft_putstr("\nTree Built\n");
		print_tree(start);
//		start = solve(start);
		ft_putstr(" = ");
		print_tree(start);
		ft_putchar('\n');
		*/
	}
	return (0);
}
