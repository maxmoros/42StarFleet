/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:11:08 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/09 12:26:16 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		null_ray(t_ray *ray)
{
	ray->dir[0] = 0;
	ray->dir[1] = 0;
	ray->sdst[0] = 0;
	ray->sdst[1] = 0;
	ray->ddst[0] = 0;
	ray->ddst[1] = 0;
	ray->step[0] = 0;
	ray->step[1] = 0;
	ray->mpos[0] = 0;
	ray->mpos[1] = 0;
	ray->pwdst = 0;
	ray->camx = 0;
	ray->side = 0;
}

t_ray		*new_ray(void)
{
	t_ray	*ray;

	if (!(ray = (t_ray*)ft_memalloc(sizeof(t_ray))))
		return (NULL);
	null_ray(ray);
	return (ray);
}

void		compute_ray(t_wolf *node)
{
	char	hit;
	int		i;

	hit = 0;
	while (!hit)
	{
		i = (node->ray->sdst[0] < node->ray->sdst[1] ? 0 : 1);
		node->ray->sdst[i] += node->ray->ddst[i];
		node->ray->mpos[i] += node->ray->step[i];
		node->ray->side = i;
		hit = (node->map->xy[node->ray->mpos[0]][node->ray->mpos[1]] ? 1 : 0);
	}
	i = node->ray->side;
	node->ray->pwdst = (node->ray->mpos[i] - node->plr->pos[i] +
						(1 - node->ray->step[i]) / 2) / node->ray->dir[i];
}

void		init_ray(t_wolf *node, double camx)
{
	int		i;

	node->ray->camx = camx;
	i = -1;
	while (++i < 2)
	{
		node->ray->dir[i] = node->plr->dir[i] + node->plr->pln[i] + camx;
		node->ray->ddst[i] = ft_math_abs(1 / node->ray->dir[i]);
		node->ray->step[i] = 0;
		if (node->ray->dir[i] < 0)
		{
			node->ray->step[i] = -1;
			node->ray->sdst[i] = (node->plr->pos[i] - node->ray->mpos[i])
								* node->ray->ddst[i];
		}
		else
		{
			node->ray->step[i] = 1;
			node->ray->sdst[i] = (node->ray->mpos[i] + 1.0 - node->plr->pos[i])
								* node->ray->ddst[i];
		}
	}
	compute_ray(node);
}

void		free_ray(t_ray *ray)
{
	if (ray)
		free(ray);
}
