/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 08:54:46 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/09 09:39:13 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bistro.h"

t_num	*neg_num(t_num *neg)
{
	if (!(neg->left = (unsigned int*)ft_memalloc(sizeof(unsigned int) * 1)) ||
		!(neg->right = (unsigned int*)ft_memalloc(sizeof(unsigned int) * 1)))
		return (NULL);
	neg->left[0] = 1;
	
	neg->ldig = 1;
	neg->rdig = 0;
	neg->sign = -1;		//-1 and 1? or 0 and 1....?
	return (neg);
}

int		cut_size(int radix)
{
	if (radix > 9)
		return (4);
	else if (radix > 6)
		return (5);
	else if (radix > 4)
		return (6);
	else if (radix == 4)
		return (8);
	else if (radix == 3)
		return (10);
	else
		return (16);
}

void	build_left(t_num *node, char *equ, char *base, unsigned int count)
{
	char	*chunk;

	if (count > 0)
	{

		chunk = ft_strndup(equ + count * node->cut - node->zeros, node->cut);
		node->left[count] = ft_atoi_base(chunk, base);
		build_left(node, equ, base, count - 1);
	}
	else
	{
		chunk = ft_strndup(equ, node->cut - node->zeros);
		node->left[0] = ft_atoi_base(chunk, base);
	}
//	free(chunk);
}

void	build_right(t_num *node, char *equ, char *base, unsigned int count)
{
	char	*chunk;

	if (count > 0)
	{
		ft_putstr("a\n");
		chunk = ft_strndup(equ - (count * node->cut) - node->zeros, node->cut);
		node->right[node->rdig / node->cut - count + 1] = ft_atoi_base(chunk, base);
		build_right(node, equ, base, count - 1);
	}
	else
	{
		ft_putstr("b\n");
		chunk = ft_strndup(equ - node->cut + node->zeros,
				node->cut - node->zeros);
		node->right[0] = ft_atoi_base(chunk, base);
	}
//	free(chunk);
}

void	build_data(t_num *node, char *start, char *end, int radix)
{
	char	*base;
	int		i;

	if(!(base = (char*)ft_memalloc(radix + 1)))
		return ;
	i = -1;
	while (++i < radix)
		base[i] = 'a' + i;
	base[i] = '\0';
	node->zeros = (node->cut - node->ldig % node->cut) % node->cut;
	ft_putstr("\nleading zeros =\t");	//###
	ft_putnbr(node->zeros);		//###
	ft_putstr("\n");			//###
	i = (node->ldig % node->cut ? node->ldig / node->cut + 1 :
		   	node->ldig / node->cut);
	i = (i ? i : 1);
	build_left(node, start, base, i);
	if (node->rdig)
	{
		node->zeros = (node->cut - node->rdig % node->cut) % node->cut;
		ft_putstr("\nending zeros =\t");	//###
		ft_putnbr(node->zeros);		//###
		ft_putstr("\n\n");	//###
		i = (node->rdig % node->cut ? node->rdig / node->cut + 1 :
			   	node->rdig / node->cut);
		i = (i ? i : 1);
		build_right(node, end, base, i - 1);
	}
//	free(base);
}

t_num	*new_num(char **equ, int radix)
{
	t_num			*node;
	unsigned int	i;
	char			*start;

	start = *equ;
	ft_putstr(start);
	if (!(node = (t_num*)malloc(sizeof(t_num))))
		return (NULL);
	if (!equ)
		return neg_num(node);
	node->ldig = 0;
	node->rdig = 0;
	node->cut = cut_size(radix);
	while (is_number(**equ, radix) && (*equ)++)
		node->ldig++;
	if (**equ == '.' && (*equ)++)
		while (is_number(**equ, radix) && (*equ)++)
			node->rdig++;
	i = (node->ldig % node->cut ? node->ldig / node->cut + 1 :
		   	node->ldig / node->cut);
	i = (i ? i : 1);
	if (!(node->left = (unsigned int*)ft_memalloc(sizeof(unsigned int) * i)))
		return (NULL);
	i = (node->rdig % node->cut ? node->rdig / node->cut + 1 :
		   	node->rdig / node->cut);
	i = (i ? i : 1);
	ft_putnbr(i);
	if (!(node->right = (unsigned int*)ft_memalloc(sizeof(unsigned int) * i)))
		return (NULL);
	node->sign = 1;

	ft_putstr("\n\nt_num example:\t");
	ft_putstr(*equ);
	ft_putstr("\ncut =\t");
	ft_putnbr(node->cut);	
//	ft_putstr("\nzeros =\t");
//	ft_putnbr(node->zeros);
	ft_putstr("\nldig =\t");
	ft_putnbr(node->ldig);	
	ft_putstr("\nrdig =\t");
	ft_putnbr(node->rdig);	
	ft_putstr("\nsign =\t");
	ft_putnbr(node->sign);	
	ft_putstr("\n\n");

	build_data(node, start, *equ, radix);
	return (node);
}

