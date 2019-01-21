/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 08:54:46 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/08 20:59:27 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_num2	*new_num2(int num2)
{
	t_num2	*node;

	if (!(node = (t_num2*)malloc(sizeof(t_num2))))
		return (NULL);
	node->value = num;
	return (node);
}

t_num2	*parse_num2(char **equ)
{
	t_num2	*node;

	node = new_num2(ft_atoi(*equ));
	while (**equ >= '0' && **equ <= '9')
		(*equ)++;
	return (node);
}
