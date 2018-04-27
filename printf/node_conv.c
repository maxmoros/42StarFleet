/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 16:40:06 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/26 14:05:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	free_conv(t_conv *node)
{
	if (node)
	{
		if (node->prefix)
			free(node->prefix);
		free(node);
	}
}

t_conv	*new_conv(int len, char *str)
{
	t_conv	*node;

	if (!(node = (t_conv*)ft_memalloc(sizeof(t_conv))))
		return (NULL);
	if (!(node->prefix = (char*)ft_memalloc(len + 1)))
	{
		free(node);
		return (NULL);
	}
	ft_strncpy(node->prefix, str, len);
	node->flags = 0;
	node->width = 0;
	node->precision = 0;
	node->next = NULL;
	node->type = 0;
	node->length = 0;
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
