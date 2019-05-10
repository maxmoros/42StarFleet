/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_512chunk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:01:25 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 19:10:10 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_512chunk	g_512chunk;

void		print_chunk(uint32_t *table)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		ft_puthex(table[i]);
		ft_putchar('\n');
	}
}

void		push_chunk()
{
	memcpy(g_512chunk.c, buf, BUF_SIZE);
	if (g_ft_ssl.debug)
		print_chunk(g_512chunk.c);
	g_ft_ssl.hash(&g_512chunk);
}

void		flip_chunk()
{
	uint32_t	x;
	uint32_t	*c;
	int			i;

	ft_putstr("Flipping chunk endian\n");
	c = g_512chunk.c;
	x = c[14];
	c[14] = c[15];
	c[15] = x;
	i = -1;
	while (++i < 14)
		c[i] = ((c[i] & 0xFF000000) >> 24) | ((c[i] & 0x00FF0000) >> 8) |
			((c[i] & 0x0000FF00) << 8) | ((c[i] & 0x000000FF) << 24);
	print_chunk(c);
}
