/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 16:58:49 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/31 20:58:47 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <stdio.h>

# define RESX 600
# define RESY 600
# define DELTA 0.04
# define DPOS(n, x, d) (n->plr->pos[x] + d)
# define MAPDIM(n, x) (n->map->dim[x])
# define MAPBLCK(n, x, y) (n->map->xy[(int)DPOS(n, 0, x)][(int)DPOS(n, 1, y)])
# define POSINMAP(n, x, d) (DPOS(n, x, d) > 0.0 && DPOS(n, x, d) < MAPDIM(n, x))



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
	double			z;
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
	char			hit;
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

typedef struct		s_img
{
	void			*ptr;
	int				*img;
	int				bits;
	int				line;
	int				endian;
}					t_img;

typedef struct		s_wolf
{
	t_map			*map;
	t_plr			*plr;
	t_ray			*ray;
	t_io			*io;
	t_img			*img;
	void			*mlx;
	void			*window;
}					t_wolf;

void				delay(int num);

int					geng(t_wolf *node);

t_map				*new_map(int x, int y);
void				print_map(t_map *map);
long				free_map(t_map *map, long out);

t_plr				*new_player(t_wolf *node);
void				move_player(t_wolf *node);
void				rotate_player(t_wolf *node);
int					print_player(t_plr *player);
void				free_player(t_plr *player);

t_ray				*new_ray(void);
void				init_ray(t_wolf *node, double camx);
void				print_ray(t_ray *ray);
void				free_ray(t_ray *ray);

t_io				*new_io(void);
void				free_io(t_io *io);

t_img				*new_img(t_wolf *node);
void				init_img(t_wolf *node);
void				pixel_to_img(t_wolf *node, int x, int y, int colour);
void				free_img(t_wolf *wolf);

t_wolf				*new_wolf_inst(int x, int y,
						unsigned int resx, unsigned int resy);
int					close_wolf(t_wolf *node);
void				*free_wolf_inst(t_wolf *node, void *out);

#endif