/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 12:45:42 by mmoros            #+#    #+#             */
/*   Updated: 2019/02/03 16:36:55 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# define L_FLAG 0x1
# define RC_FLAG 0x2
# define A_FLAG 0x4
# define RV_FLAG 0x8
# define T_FLAG 0x10

# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <pwd.h>
# include <grp.h>

typedef struct		s_dir
{
	char			*path;
	struct stat		*stat;
	struct dirent	*data;
	struct s_dir	*up;
	struct s_dir	*in;
	struct s_dir	*next;
}					t_dir;

t_dir				*get_nodes(DIR *dir, t_dir *up, char flags);
char				*node_path(t_dir *node);

void				print_nodes(t_dir *node, char flags);

void				delay(int num);

#endif
