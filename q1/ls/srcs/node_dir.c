/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:40:59 by mmoros            #+#    #+#             */
/*   Updated: 2019/07/12 14:49:33 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_dir	*new_dir(char *d_name, t_dir *up, t_dir *list)
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
	return (insert_node(list, node));
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
				S_ISDIR(MODE(node)) && !S_ISLNK(MODE(node)))
		{
			ft_pbs("\n%s:\n", node->path);
			if ((node->dir = opendir(node->path)))
			{
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
			else
				ft_pbs("ls: %s: Permission denied\n", node->d_name);
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
		root = new_dir(dp->d_name, up, root);
	if (!root)
		return (NULL);
	print ? print_nodes(root) : 0;
	FLAG_SET(RC_FLAG) && print ? recurse_node(root) : 0;
	return (root);
}
