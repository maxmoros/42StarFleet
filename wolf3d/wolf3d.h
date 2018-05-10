/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:58:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/09 20:08:29 by mmoros           ###   ########.fr       */
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
	int				theta;
	double			dir[2];
	double			pln[2];
}					t_plr;

typedef struct		s_ray
{
	double			dir[2];
	double			sdst[2];
	double			ddst[2];
	int				step[2];
	int				mpos[2];
	double			pwdst;
	double			camx;
	char			side;
}					t_ray;

typedef struct		s_io
{
	char			a;
	char			s;
	char			d;
	char			w;
	char			space;
	char			esc;
}					t_io;

typedef struct		s_wolf
{
	t_map			*map;
	t_plr			*plr;
	t_ray			*ray;
	t_io			*io;
	void			*mlx;
	void			*window;
}					t_wolf;

void				delay(int num);

int					geng(t_wolf *node);

t_map				*new_map(int x, int y);
void				print_map(t_map *map);
long				free_map(t_map *map, long out);

t_plr				*new_player(void);
void				move_player(t_wolf *node);
int					print_player(t_plr *player);
void				free_player(t_plr *player);

t_ray				*new_ray(void);
void				init_ray(t_wolf *node, double camx);
void				print_ray(t_ray *ray);
void				free_ray(t_ray *ray);

t_io				*new_io(void);
void				free_io(t_io *io);

t_wolf				*new_wolf_inst(int x, int y,
						unsigned int resx, unsigned int resy);
void				*free_wolf_inst(t_wolf *node, void *out);

#endif