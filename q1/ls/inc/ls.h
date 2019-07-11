/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:45:42 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/10 16:01:20 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# define L_FLAG 0x1
# define RC_FLAG 0x2
# define A_FLAG 0x4
# define RV_FLAG 0x8
# define T_FLAG 0x10
# define S_FLAG 0x20
# define PATH_MAX 4096

# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>

# define ST_MODE(n, x)	(n->stat->st_mode & x)
# define NODE_IN		(node->in ? node->in : 								\
							get_nodes(opendir(node->path), node))
# define FLAG_SET(f)	(g_flags & f)
# define CMP_DIR(str)	ft_strcmp(node->data->d_name, str)

typedef struct		s_dir
{
	char			*path;
	DIR				*dir;
	struct s_dir	*in;
	struct stat		*stat;
	struct dirent	*data;
	struct s_dir	*up;
	struct s_dir	*next;
}					t_dir;

extern char			*g_root_offset;
extern uint8_t		g_flags;

t_dir				*get_nodes(DIR *dir, t_dir *up);
char				*node_path(t_dir *node);

void				print_nodes(t_dir *node);
void				print_longf_nodes(t_dir *node);

uint8_t				ft_numlen(int num);

void				delay(int num);

#endif
