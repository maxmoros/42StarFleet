/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 21:11:08 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/07 09:28:30 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		null_ray(t_ray *ray)
{
	ray->sdst[0] = 0;
	ray->sdst[1] = 0;
	ray->ddst[0] = 0;
	ray->ddst[1] = 0;
	ray->step[0] = 0;
	ray->step[1] = 0;
	ray->pos[0] = 0;
	ray->pos[1] = 0;
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

void		free_ray(t_ray *ray)
{
	if (ray)
		free(ray);
}