/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:45:42 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/12 14:19:59 by mmoros           ###   ########.fr       */
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

# define ST_MODE(s, x)	(s->st_mode & x)
# define FLAG_SET(f)	(g_flags & f)
# define REV_ON			((g_flags & RV_FLAG) > 0)
# define CMP_DIR(str)	ft_strcmp(node->d_name, str)
# define BLOCKS(n)		(n->stat->st_blocks)
# define SIZE(n)		(n->stat->st_size)
# define MODE(n)		(n->stat->st_mode)
# define MTIME(n)		(n->stat->st_mtime)
# define CTIME(n)		(ctime(&MTIME(n)))
# define NAME(n)		(n->d_name)
# define PW_NAME(n)		(getpwuid(n->stat->st_uid))
# define GR_NAME(n)		(getgrgid(n->stat->st_gid))

typedef struct		s_dir
{
	char			*path;
	DIR				*dir;
	struct s_dir	*in;
	struct stat		*stat;
	char			*d_name;
	struct s_dir	*up;
	struct s_dir	*next;
}					t_dir;

extern char			*g_root_offset;
extern uint8_t		g_flags;

t_dir				*new_dir(char *d_name, t_dir *up, t_dir *next);
t_dir				*get_nodes(DIR *dir, t_dir *up, uint8_t print);
t_dir				*insert_node(t_dir *n1, t_dir *n2);
void				node_path(t_dir *node);
int					free_nodes(t_dir *node);

void				print_nodes(t_dir *node);
void				print_links(t_dir *node);
void				print_id(t_dir *node);
void				print_permissions(struct stat *stat);
void				print_size(t_dir *node, int offset);
void				print_date_mod(t_dir *node);
void				print_longf_nodes(t_dir *node);
int					check_symlink(char *path);
void				print_symlink(char *path);

uint8_t				ft_numlen(int num);

#endif
