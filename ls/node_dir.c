/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:40:59 by mmoros            #+#    #+#             */
/*   Updated: 2018/05/05 13:21:57 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_dir	*new_dir(struct dirent *data, t_dir *up, t_dir *in, t_dir *next)
{
	t_dir	*node;

	if (!(node = (t_dir*)ft_memalloc(sizeof(t_dir))))
		return (NULL);
	node->data = data;
	node->up = up;
	node->in = in;
	node->next = next;
	return (node);
}

/*
**If time permits, replace this p.o.s.
*/

t_dir	*sort_list(t_dir *list, char flags, int (*cmp)(t_dir*, t_dir*, char))
{
	struct dirent	*tmp;
	t_dir			*node;

	node = list;
	while (node->next)
	{
		if (cmp(node, node->next, flags))
			node = node->next;
		else
		{
			printf("swap : n1 = \"%s\", n2 = \"%s\"\n",
				node->data->d_name, node->next->data->d_name);
			tmp = node->data;
			node->data = node->next->data;
			node->next->data = tmp;
			node = list;
		}
	}
	return (list);
}

int		cmp_time(t_dir *n1, t_dir *n2, char flags)
{
	struct stat		stat_n1;
	struct stat		stat_n2;

	if (stat(n1->data->d_name, &stat_n1) == -1 ||
		stat(n2->data->d_name, &stat_n2) == -1)
		return (-1);
	flags &= T_FLAG;
	printf("time : stat_n1 = %d, stat_n2 = %ld\n", (int)stat_n1.st_mtime, stat_n2.st_mtime);
	printf("dif = %d\n", (int)stat_n1.st_mtime - (int)stat_n2.st_mtime);
	if (stat_n1.st_mtime - stat_n1.st_mtime >= 0)// ^ !(flags & RV_FLAG))
		return (1);
	return (0);
}

int		cmp_lexi(t_dir *n1, t_dir *n2, char fg)
{
	if ((ft_strcmp(n1->data->d_name, n2->data->d_name) > 0) ^ !(fg & RV_FLAG))
		return (1);
	return (0);
}

void	recurse_node(t_dir *node, char flags)
{
	struct stat		stats;
	char			*path;
	DIR				*dir

	while (node)
	{
		node_path(node, &path);
		if (stat(path, &stats) == -1)
			return ;
		dir = opendir(path);
		if (stats.st_mode & S_IFDIR)
			node->in = get_nodes(dir, node, flags);
		node = node->next;
		closedir(dir);
	}
}

t_dir	*get_nodes(DIR *dir, t_dir *up, char flags)
{
	t_dir			*root;
	t_dir			*node;
	struct dirent	*dp;

	if (!(dp = readdir(dir)))
		return (NULL);
	root = new_dir(dp, up, NULL, NULL);
	while ((dp = readdir(dir)))
		root = new_dir(dp, up, NULL, root);
	root = sort_list(root, flags, (flags & T_FLAG ? cmp_time : cmp_lexi));
	if (flags & RC_FLAG)
		recurse_node(root, flags);
	return (root);
}