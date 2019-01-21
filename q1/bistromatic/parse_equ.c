/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_equ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 09:01:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/09 09:14:18 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"
#include <time.h>

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Stroing start time
    clock_t start_time = clock();

    // looping till required time is not acheived
    while (clock() < start_time + milli_seconds)
        ;
}

void	clean_equ(char **equ)
{
	while (**equ == ' ' || **equ == '\t')
		(*equ)++;
}

int		is_opperator(char equ)
{
	if (equ == '+' || equ == '-' ||
		equ == '*' || equ == '/' ||
		equ == '%')
		return (1);
	return (0);
}

int		is_number(char equ, int radix)
{
	if (equ >= 'a' && equ <= 'a' + radix)
		return (1);
	return (0);
}

t_equ	*push_left(t_equ *left, char **equ)
{
	t_equ	*node;

	node = new_equ(**equ, left->up, left, NULL);
	if (left->up)
	{
		if (left->up->left == left)
			left->up->left = node;
		else
			left->up->right = node;
	}
	left->up = node;
	(*equ)++;
	return (node);
}
//Only two functions usint t_num :D
t_equ	*equ_value(t_equ *parent, char **equ, int radix)
{
	t_equ	*node;

	node = new_equ(0, parent, NULL, NULL);
	if (equ)
		node->value = new_num(equ, radix);
	else
		node->value = new_num(NULL, radix);
	return (node);
}
//Second one using t_num :D
t_equ	*home_right_neg(t_equ *parent)
{
	t_equ	*node;
	t_equ	*neg;

	node = new_equ('*', parent, NULL, NULL);
	neg = new_equ(0, node, NULL, NULL);
	node->left = neg;
	neg->value = new_num(NULL, 0);
	return (node);
}

int		home_right_num(t_equ *parent, char **equ, int radix)
{
	t_equ	*node;
	t_equ	*right;

	node = new_equ(**equ, parent, parent->right, NULL);
	(*equ)++;
	clean_equ(equ);
	ft_putchar(**equ);	//###
	delay(500);			//###
	ft_putchar('k');	//###
	parent->right = node;
	node->left->up = node;

	if (is_number(**equ, radix))
		right = equ_value(node, equ, radix);
	else if (**equ == '(' && (*equ)++)
	{
		right = equ_home(node, equ, radix);
	}
	else
		return (0);
	node->right = right;
	return (1);
}

t_equ	*equ_home(t_equ *parent, char **equ, int radix)
{
	t_equ	*home;
	
	home = new_equ(0, parent, NULL, NULL);
	while (**equ && **equ != ')')
	{
		ft_putchar(**equ);
		delay(500);
		if (home->right || home->value)
		{
			if (is_opperator(**equ))		//New Function	/
			{
				if (home->right && **equ != '+' && **equ != '-' &&
					home->op != '*' && home->op != '/' && home->op != '%')
				{
					ft_putchar('j');
					if(!home_right_num(home, equ, radix))		//New Function	/
						return (NULL);
				}
				else
				{
					ft_putchar('f');
					home = push_left(home, equ);		//New Function	/
				}
			}
			else if (**equ == ')')			//Likely redundant
				return (home);
			else
				return (NULL);
		}
		else if (home->left)
		{
			if (home->op)
			{
				if (**equ == '-' && (*equ)++)
				{
					home_right_neg(home);	//New Function
					ft_putchar('g');	//###
				}
				else if (**equ == '(' && ++(*equ))
				{
					if(!(home->right = equ_home(home, equ, radix)))
						return (NULL);
				}
				else if (is_number(**equ, radix))		//New Function / temp soln
				{
					home->right = equ_value(home, equ, radix);	//New Function	/
					ft_putchar('c'); //###
				}
				else
					return NULL;	//Parse Error
			}
			else if (is_opperator(**equ))	//New Function 	/
			{
				home->op = **equ;
				(*equ)++;
				ft_putchar('b'); //###
			}
			else if (**equ)		//EOF case, Redundant??
				return NULL;	//Parse Error
			else
				return (home);	//Redundant?? 
		}
		else if (**equ == '-' && (*equ)++)
		{
			home->left = equ_value(home, NULL, radix);	//have equ_value understand set -1 /
			home->op = '*';
			ft_putchar('e');	//###
		}
		else if (**equ == '(' && (*equ)++)
		{
			if(!(home->left = equ_home(home, equ, radix)))		//KaPOW!!
				return (NULL);
		}
		else if (is_number(**equ, radix))
		{
			home->left = equ_value(home, equ, radix);
			ft_putchar('a'); //###
		}
		else
			return NULL;		//Parse Error
		clean_equ(equ);			//make sure only used characters skipped over...
	}
	if (**equ == ')' && home->up)		//Careful here....
	{
		(*equ)++;
		ft_putchar('h');
	}
	else if (**equ == ')' || home->up)
	{
		ft_putchar('i');
		return (NULL);
	}
	clean_equ(equ);			//make sure only used characters skipped over...
	return (home);
}
