/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:11:08 by mmoros            #+#    #+#             */
/*   Updated: 2018/08/30 19:42:06 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_ray		*new_ray(void)
{
	t_ray	*ray;

	if (!(ray = (t_ray*)ft_memalloc(sizeof(t_ray))))
		return (NULL);
	return (ray);
}

static void	ray_nesw(t_ray *ray)
{
	if (ray->step[0] > 0 && ray->step[1] > 0)
		ray->side = (ray->side ? 0 : 3);
	else if (ray->step[0] > 0)
		ray->side = (ray->side ? 2 : 3);
	else if (ray->step[1] > 0)
		ray->side = (ray->side ? 0 : 1);
	else
		ray->side = (ray->side ? 2 : 1);
}

void		compute_ray(t_wolf *node)
{
	t_ray	*ray;
	int		i;

	ray = node->ray;
	ray->hit = 0;
	while (!ray->hit && RAY_IN_MAP(0) && RAY_IN_MAP(1))
	{
		i = (ray->sdst[0] < ray->sdst[1] ? 0 : 1);
		ray->sdst[i] += ray->ddst[i];
		ray->mpos[i] += ray->step[i];
		ray->side = i;
		if (RAY_IN_MAP(0) && RAY_IN_MAP(1) && RAY_IN_WALL)
			ray->hit = 1;
	}
	ray->pwdst = (ray->mpos[i] - node->plr->pos[i] +
						(1 - ray->step[i]) / 2) / ray->dir[i];
	if (ray->side)
		ray->wallx = fmod(node->plr->pos[0] + ray->pwdst * ray->dir[0], 1.0);
	else
		ray->wallx = fmod(node->plr->pos[1] + ray->pwdst * ray->dir[1], 1.0);
	if ((ray->step[0] < 0 && !ray->side) || (ray->step[1] > 0 && ray->side))
		ray->wallx = 1 - ray->wallx;
	ray_nesw(ray);
}

void		init_ray(t_wolf *node, double camx)
{
	int		i;

	node->ray->camx = camx;
	i = -1;
	while (++i < 2)
	{
		node->ray->mpos[i] = node->plr->pos[i];
		node->ray->dir[i] = node->plr->dir[i] + node->plr->pln[i] * camx;
		node->ray->ddst[i] = ft_math_dabs(1 / node->ray->dir[i]);
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
