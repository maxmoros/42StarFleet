/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 14:00:48 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/09 09:17:08 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_equ	*mul(t_equ *a, t_equ *b)
{
	if (a->op)
		a = solve(a);
	if (b->op)
		b = solve(b);
	a->value->value *= b->value->value;
	return (a);
}

t_equ	*divide(t_equ *a, t_equ *b)
{
	if (a->op)
		a = solve(a);
	if (b->op)
		b = solve(b);
	a->value->value /= b->value->value;
	return (a);
}

t_equ	*add(t_equ *a, t_equ *b)
{
	if (a->op)
		a = solve(a);
	if (b->op)
		b = solve(b);
	a->value->value += b->value->value;
	return (a);
}

t_equ	*sub(t_equ *a, t_equ *b)
{
	if (a->op)
		a = solve(a);
	if (b->op)
		b = solve(b);
	a->value->value -= b->value->value;
	return (a);
}

t_equ	*mod(t_equ *a, t_equ *b)
{
	if (a->op)
		a = solve(a);
	if (b->op)
		b = solve(b);
	a->value->value = a->value->value % b->value->value;
	return (a);
}

t_equ	*solve(t_equ *equ)
{
	if (equ->op)
	{
		if (equ->op == '*')
			return (mul(equ->left, equ->right));
		else if (equ->op == '/')
			return (divide(equ->left, equ->right));
		else if (equ->op == '+')
			return (add(equ->left, equ->right));
		else if (equ->op == '-')
			return (sub(equ->left, equ->right));
		else if (equ->op == '%')
			return (mod(equ->left, equ->right));
	}
	else if (equ->value)
		return (equ);
	return (solve(equ->left));
}
