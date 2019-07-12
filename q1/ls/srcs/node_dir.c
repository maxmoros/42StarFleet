/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:40:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/11 21:35:21 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_dir	*new_dir(char *d_name, t_dir *up, t_dir *next)
{
	t_dir	*node;

	if (!(node = (t_dir*)ft_memalloc(sizeof(t_dir))) ||
		!(node->stat = (struct stat*)ft_memalloc(sizeof(struct stat))))
		return (NULL);
	node->dir = NULL;
	node->d_name = ft_strdup(d_name);
	node->up = up;
	node->in = NULL;
	node->next = next;
	node_path(node);
	lstat(node->path, node->stat);
	return (node);
}

t_dir	*sort_list(t_dir *list, int (*cmp)(t_dir*, t_dir*))
{
	char			*tmp;
	struct stat		*stats;
	char			*str;
	t_dir			*node;

	node = list;
	while (node->next)
		if (cmp(node, node->next))
			node = node->next;
		else
		{
			tmp = node->d_name;
			str = node->path;
			stats = node->stat;
			node->d_name = node->next->d_name;
			node->path = node->next->path;
			node->stat = node->next->stat;
			node->next->d_name = tmp;
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

	if (stat(NAME(n1), &stat_n1) == -1 ||
		stat(NAME(n2), &stat_n2) == -1)
		return (-1);
	FLAG_SET(T_FLAG);
	printf("time : stat_n1 = %d, stat_n2 = %ld\n", (int)stat_n1.st_mtime, stat_n2.st_mtime);
	printf("dif = %d\n", (int)stat_n1.st_mtime - (int)stat_n2.st_mtime);
	return (stat_n1.st_mtime - stat_n1.st_mtime >= 0);
}

int		cmp_lexi(t_dir *n1, t_dir *n2)
{
	return ((ft_strcmp(NAME(n1), NAME(n2)) > 0) ^ !(FLAG_SET(RV_FLAG)));
}

void	node_path(t_dir *node)
{
	int		length;
	int		tmp_len;
	t_dir	*tmp;

	length = (g_root_offset ? ft_strlen(g_root_offset) + 1 : 0);
	tmp = node;
	while (tmp)
	{
		length += 1 + ft_strlen(NAME(tmp));
		tmp = tmp->up;
	}
	if (!(node->path = (char*)ft_memalloc(sizeof(char) * (length))))
		return ;
	node->path[--length] = '\0';
	tmp = node;
	while (tmp)
	{
		tmp_len = ft_strlen(NAME(tmp));
		ft_strncpy(node->path + (length -= tmp_len), NAME(tmp), tmp_len);
		node->path[--length] = '/';
		tmp = tmp->up;
	}
	if (g_root_offset)
		ft_strncpy(node->path, g_root_offset, ft_strlen(g_root_offset));
}

void	recurse_node(t_dir *node)
{
	while (node)
	{
		if (CMP_DIR(".") && CMP_DIR("..") &&
				(FLAG_SET(A_FLAG) || !(NAME(node)[0] == '.')) &&
				S_ISDIR(MODE(node)) && !S_ISLNK(MODE(node)) &&
				(node->dir = opendir(node->path)))
			node->in = get_nodes(node->dir, node, 1);
		node = node->next;
	}
}

t_dir	*get_nodes(DIR *dir, t_dir *up, uint8_t sort)
{
	t_dir			*root;
	struct dirent	*dp;

	root = NULL;
	while ((dp = readdir(dir)))
		root = new_dir(dp->d_name, up, root);
	if (!root)
		return (NULL);
	if (sort)
		root = sort_list(root, (FLAG_SET(T_FLAG) ? cmp_time : cmp_lexi));
	if (FLAG_SET(RC_FLAG))
		recurse_node(root);
	return (root);
}

int		free_nodes(t_dir *node)
{
	t_dir	*tmp;

	while (node)
	{
		free(node->path);
		node->in ? free_nodes(node->in) : 0;
		node->stat ? free(node->stat) : 0;
		free(node->d_name);
		tmp = node;
		node = node->next;
		free(tmp);
	}
	return (0);
}
