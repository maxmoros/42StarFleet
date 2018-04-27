/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grimly.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:59:19 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/16 20:59:36 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRIMLY_H
# define GRIMLY_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct		s_actor
{
	int				x;
	int				y;
	struct s_actor	*next;
}					t_actor;

char				***grim_init(int *xy);
int					grim_solve(char ***map, int *xy);
t_actor				*grim_actor(t_actor *next, int x, int y);
void				free_actors(t_actor *node);
int					grim_del(t_actor **node);
int					grim_close(char ***map, int *xy, int out, int mapset);
int					grim_ulr(char ***map, t_actor *node, int *xy);
int					grim_uld(char ***map, t_actor *node, int *xy);
int					grim_urd(char ***map, t_actor *node, int *xy);
int					grim_lrd(char ***map, t_actor *node, int *xy);
int					grim_ul(char ***map, t_actor *node, int *xy);
int					grim_ur(char ***map, t_actor *node, int *xy);
int					grim_ud(char ***map, t_actor *node, int *xy);
int					grim_lr(char ***map, t_actor *node, int *xy);
int					grim_ld(char ***map, t_actor *node, int *xy);
int					grim_rd(char ***map, t_actor *node, int *xy);
int					grim_u(char ***map, t_actor *node, int *xy);
int					grim_l(char ***map, t_actor *node, int *xy);
int					grim_r(char ***map, t_actor *node, int *xy);
int					grim_d(char ***map, t_actor *node, int *xy);

#endif
