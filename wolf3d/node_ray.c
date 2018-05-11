/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:11:08 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/10 20:03:18 by mmoros           ###   ########.fr       */
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
	t_ray	*ray;
	int		i;

	ray = node->ray;
	ray->hit = 0;
	while (!ray->hit && ray->mpos[0] >= 0 && ray->mpos[0] < node->map->dim[0]
					&& ray->mpos[1] >= 0 && ray->mpos[1] < node->map->dim[1])
	{
		i = (ray->sdst[0] < ray->sdst[1] ? 0 : 1);
		ray->sdst[i] += ray->ddst[i];
		ray->mpos[i] += ray->step[i];
		ray->side = i;
		if (ray->mpos[0] >= 0 && ray->mpos[0] < node->map->dim[0]
					&& ray->mpos[1] >= 0 && ray->mpos[1] < node->map->dim[1])
			ray->hit = (node->map->xy[ray->mpos[0]][ray->mpos[1]]
							!= '0' ? 1 : 0);
	}
	i = ray->side;
	ray->pwdst = (ray->mpos[i] - node->plr->pos[i] +
						(1 - ray->step[i]) / 2) / ray->dir[i];
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

void		print_ray(t_ray *ray)
{
	printf("Ray:\tdir = (%f, %f)\n\t\tsdst = (%f, %f)\n\t\tddst = (%f, %f)\n",
			ray->dir[0], ray->dir[1],
			ray->sdst[0], ray->sdst[1],
			ray->ddst[0], ray->ddst[1]);
	printf("\t\tstep = (%d, %d)\n\t\tmpos = (%d, %d)\n",
			ray->step[0], ray->step[1],
			ray->mpos[0], ray->mpos[1]);
	printf("\t\tcamx = %f\tside = %d\n\t\tpwdst = %f\n",
			ray->camx, ray->side, ray->pwdst);
}

void		free_ray(t_ray *ray)
{
	if (ray)
		free(ray);
}
