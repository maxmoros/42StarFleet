/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_equ.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 08:53:55 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/08 20:59:18 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_equ	*new_equ(char op, t_equ *up, t_equ *left, t_num *value)
{
	t_equ	*node;

	if(!(node = (t_equ*)malloc(sizeof(t_equ))))
		return (NULL);
	node->op = op;
	node->up = up;
	node->left = left;
	node->right = NULL;
	node->value = value;
	return (node);
}
