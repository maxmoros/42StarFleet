/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:40:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/10 16:01:23 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_dir	*new_dir(struct dirent *data, t_dir *up, t_dir *next)
{
	t_dir	*node;

	if (!(node = (t_dir*)ft_memalloc(sizeof(t_dir))) ||
		!(node->stat = (struct stat*)ft_memalloc(sizeof(struct stat))))
		return (NULL);
	node->dir = NULL;
	node->data = data;
	node->up = up;
	node->in = NULL;
	node->next = next;
	node->path = node_path(node);
	lstat(node->path, node->stat);
	return (node);
}

/*
**If time permits, replace this p.o.s.
*/

t_dir	*sort_list(t_dir *list, int (*cmp)(t_dir*, t_dir*))
{
	struct dirent	*tmp;
	struct stat		*stats;
	char			*str;
	t_dir			*node;

	node = list;
	while (node->next)
		if (cmp(node, node->next))
			node = node->next;
		else
		{
			tmp = node->data;
			str = node->path;
			stats = node->stat;
			node->data = node->next->data;
			node->path = node->next->path;
			node->stat = node->next->stat;
			node->next->data = tmp;
			node->next->path = str;
			node->next->stat = stats;
			node = list;
		}
	return (list);
}

int		cmp_time(t_dir *n1, t_dir *n2)
{
	struct stat		stat_n1;
	struct stat		stat_n2;

	if (stat(n1->data->d_name, &stat_n1) == -1 ||
		stat(n2->data->d_name, &stat_n2) == -1)
		return (-1);
	FLAG_SET(T_FLAG);		//WHY?
	printf("time : stat_n1 = %d, stat_n2 = %ld\n", (int)stat_n1.st_mtime, stat_n2.st_mtime);
	printf("dif = %d\n", (int)stat_n1.st_mtime - (int)stat_n2.st_mtime);
	return (stat_n1.st_mtime - stat_n1.st_mtime >= 0);// ^ !(g_flags & RV_FLAG))
}

int		cmp_lexi(t_dir *n1, t_dir *n2)
{
	return ((ft_strcmp(n1->data->d_name, n2->data->d_name) > 0) ^
											!(FLAG_SET(RV_FLAG)));
}

char	*node_path(t_dir *node)
{
	int		length;
	int		tmp_len;
	t_dir	*tmp;
	char	*path;

	length = ft_strlen(g_root_offset) + 1;
	tmp = node;
	while (tmp)
	{
		length += 1 + ft_strlen(tmp->data->d_name);
		tmp = tmp->up;
	}
	if (!(path = (char*)ft_memalloc(sizeof(char) * (length))))
		return (NULL);
	path[length - 1] = '\0';
	length--;
	tmp = node;
	while (tmp)
	{
		tmp_len = ft_strlen(tmp->data->d_name);
		ft_strncpy(path + (length -= tmp_len), tmp->data->d_name, tmp_len);
		path[--length] = '/';
		tmp = tmp->up;
	}
	ft_strncpy(path, g_root_offset, ft_strlen(g_root_offset));
	return (path);
}

void	recurse_node(t_dir *node)
{
	while (node)
	{
		if (CMP_DIR(".") && CMP_DIR("..") &&
				!((FLAG_SET(A_FLAG)) ^ (node->data->d_name[0] == '.')) &&
				ST_MODE(node, S_IFDIR) && (node->dir = opendir(node->path)))
			node->in = get_nodes(node->dir, node);
		node = node->next;
	}
}

t_dir	*get_nodes(DIR *dir, t_dir *up)
{
	t_dir			*root;
	struct dirent	*dp;

	root = NULL;
	while ((dp = readdir(dir)))
		root = new_dir(dp, up, root);
	if (!root)
		return (NULL);
	root = sort_list(root, (FLAG_SET(T_FLAG) ? cmp_time : cmp_lexi));
	if (FLAG_SET(RC_FLAG))
		recurse_node(root);
	return (root);
}
