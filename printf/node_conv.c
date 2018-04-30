/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:40:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/29 23:17:17 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

t_conv	*free_conv(t_conv *node)
{
	t_conv	*tmp;

	while (node)
	{
		if (node->prefix)
			free(node->prefix);
		tmp = node;
		node = node->next;
		free(tmp);
	}
	return (NULL);
}

t_conv	*new_conv(char **str)
{
	t_conv	*node;

	if (!(node = (t_conv*)ft_memalloc(sizeof(t_conv))))
		return (NULL);
	node->i = ft_strlen_c(*str, '%');
	if (!(node->prefix = (char*)ft_memalloc(node->i + 1)))
	{
		free(node);
		return (NULL);
	}
	ft_strncpy(node->prefix, *str, node->i);
	(*str) += node->i;
	node->flags = 0;
	node->width = 0;
	node->precision = 0;
	node->next = NULL;
	node->type = 0;
	node->length = 0;
	node->j = 0;
	node->padding = 0;
	return (node);
}

void	print_nodes(t_conv *node)
{
	int		i;

	i = 0;
	while (node)
	{
		ft_putstr("NODE#");
		ft_putnbr(i++);
		ft_putstr(":: \tprefix is \"");
		ft_putstr(node->prefix);
		ft_putstr("\"\n\t\tf: ");
		ft_puthex(node->flags);
		ft_putstr(", w = ");
		ft_putnbr(node->width);
		ft_putstr(", p = ");
		ft_putnbr(node->precision);
		ft_putstr(", l: ");
		ft_puthex(node->length);
		ft_putstr("\n\n");
		node = node->next;
	}
}

t_conv	*pf_chomp(char *str, char *error)
{
	t_conv	*node;
	int		i;

	node = new_conv(&str);
	if (*str && !*error)
	{
		if (!(parse_conv(str, node, &i)))
			*error = 1;
		if (*(str += i) && !*error)
			node->next = pf_chomp(str, error);
	}
	return (*error ? free_conv(node) : node);
}

int		sum_printed(t_conv *node)
{
	int		sum;
	t_conv	*tmp;

	sum = 0;
	tmp = node;
	while (tmp)
	{
		sum += tmp->j + tmp->i;
		tmp = tmp->next;
	}
	return (sum);
}
