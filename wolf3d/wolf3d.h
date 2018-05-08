/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:58:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/08 10:10:09 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>

typedef struct		s_map
{
	char			**xy;
	int				dim[2];
}					t_map;

typedef struct		s_plr
{
	double			pos[2];
	double			dir[2];
	double			pln[2];
}					t_plr;

typedef struct		s_ray
{
	double			sdst[2];
	double			ddst[2];
	int				step[2];
	int				pos[2];
	double			pwdst;
	double			camx;
	char			side;
}					t_ray;

typedef struct		s_wolf_inst
{
	t_map			*map;
	t_plr			*plr;
	t_ray			*ray;
	void			*mlx;
	void			*window;
}					t_wolf_inst;

t_map				*new_map(int x, int y);
void				print_map(t_map *map);
long				free_map(t_map *map, long out);

t_plr				*new_player(void);
void				free_player(t_plr *player);

t_ray				*new_ray(void);
void				free_ray(t_ray *ray);

t_wolf_inst			*new_wolf_inst(int x, int y,
						unsigned int resx, unsigned int resy);
long				free_wolf_inst(t_wolf_inst *node, long out);

#endif