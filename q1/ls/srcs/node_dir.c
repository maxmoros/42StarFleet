/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:40:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/12 13:47:51 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		cmp_lexi(t_dir *n1, t_dir *n2)
{
	return (ft_strcmp(NAME(n1), NAME(n2)) < 0);
}

int		cmp_time(t_dir *n1, t_dir *n2)
{
	if (MTIME(n1) == MTIME(n2))
	{
		ft_pbs("SAME TIME! n1[%s], n2[%s], cmp=%d\n", NAME(n1), NAME(n2), cmp_lexi(n1, n2));
		return (cmp_lexi(n1, n2));
	}
	return ((MTIME(n1) - MTIME(n2)) >= 0);
}

t_dir	*insert_node(t_dir *n1, t_dir *n2)
{
	int		(*cmp)(t_dir*, t_dir*);
	t_dir	*tmp;

	cmp = (FLAG_SET(T_FLAG) ? cmp_time : cmp_lexi);
	if (REV_ON ^ cmp(n2, n1))
	{
		n2->next = n1;
		return (n2);
	}
	tmp = n1;
	while (tmp->next && (REV_ON ^ cmp(tmp->next, n2)))
		tmp = tmp->next;
	if (tmp->next)
		n2->next = tmp->next;
	tmp->next = n2;
	return (n1);
}

t_dir	*new_dir(char *d_name, t_dir *up, t_dir *list, uint8_t sort)
{
	t_dir	*node;

	if (!(node = (t_dir*)ft_memalloc(sizeof(t_dir))) ||
		!(node->stat = (struct stat*)ft_memalloc(sizeof(struct stat))))
		return (NULL);
	node->d_name = ft_strdup(d_name);
	node->up = up;
	node_path(node);
	lstat(node->path, node->stat);
	if (!list)
		return (node);
	node->next = (sort ? NULL : list);
	return (sort ? insert_node(list, node) : node);
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
		ft_bzero(tmp, sizeof(t_dir));
		free(tmp);
	}
	return (0);
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
		if (length)
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
		{
			ft_pbs("\n%s:\n", node->path);
			if (FLAG_SET(L_FLAG))
			{
				print_nodes(node->in);
				recurse_node(node->in);
			}
			else
				node->in = get_nodes(node->dir, node, 1);
			closedir(node->dir);
			free_nodes(node->in);
			node->in = NULL;
		}
		node = node->next;
	}
}

t_dir	*get_nodes(DIR *dir, t_dir *up, uint8_t print)
{
	t_dir			*root;
	struct dirent	*dp;

	root = NULL;
	while ((dp = readdir(dir)))
		root = new_dir(dp->d_name, up, root, print);
	if (!root)
		return (NULL);
	print ? print_nodes(root) : 0;
	FLAG_SET(RC_FLAG) && print ? recurse_node(root) : 0;
	return (root);
}
