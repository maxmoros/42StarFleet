/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:15:40 by mmoros            #+#    #+#             */
/*   Updated: 2018/04/03 18:47:30 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl		*f_n(const int fd, t_gnl *next)
{
	t_gnl	*node;
	int		i;

	if (!(node = (t_gnl*)malloc(sizeof(t_gnl))))
		return (0);
	node->fd = fd;
	node->next = next;
	node->right = NULL;
	node->i = 0;
	node->read = 0;
	node->out = 1;
	i = -1;
	while (++i < BUFF_SIZE)
		node->buff[i] = '\0';
	return (node);
}

t_gnl		*fd_node_get(const int fd, t_gnl **lst)
{
	t_gnl		*node;

	node = *lst;
	if (*lst)
	{
		while (node->right && fd != node->fd)
			node = node->right;
		if (fd == node->fd)
			return (node);
		node->right = f_n(fd, NULL);
		return (node->right);
	}
	return (*lst = f_n(fd, NULL));
}

int			get_l(char **line, t_gnl *node, int index, t_gnl *mn)
{
	if ((node->read = read(node->fd, node->buff, BUFF_SIZE)) > 0 || index > 0)
	{
		while (node->i < node->read && node->buff[node->i] != '\n')
			node->i++;
		if ((node->i < node->read || node->read < BUFF_SIZE))
		{
			if (!(*line = (char*)ft_memalloc(sizeof(char) *
				(BUFF_SIZE * index + node->i + (mn->read) + 1))))
				return (-1);
			ft_memcpy(*line, mn->buff, mn->read);
			mn->fd = node->read - node->i - 1;
			if (node->i < node->read)
				ft_memcpy(mn->buff, node->buff + node->i + 1, mn->fd);
		}
		else
			node->out = get_l(line, f_n(node->fd, node->next), index + 1, mn);
		ft_memcpy(*line + BUFF_SIZE * index + (mn->read), node->buff, node->i);
	}
	else if (node->read < 0)
		node->out = -1;
	else if (index == 0)
		node->out = 0;
	free(node);
	return (node->out);
}

void		get_master(char **line, t_gnl *mn, int *out)
{
	if (mn->read > 0 && (*out = 1))
	{
		while (mn->i < mn->read && mn->buff[mn->i] != '\n')
			mn->i++;
		if (mn->i < mn->read || !(*out = get_l(line, f_n(mn->fd, NULL), 0, mn)))
		{
			*out = 1;
			if (!(*line = (char*)ft_memalloc((mn->i + 1))))
				*out = -1;
			ft_memcpy(*line, mn->buff, mn->i);
			if (mn->i < mn->read && *out != -1)
			{
				mn->read = mn->read - mn->i - 1;
				ft_memcpy(mn->buff, mn->buff + mn->i + 1, mn->read);
				ft_memset(mn->buff + mn->read, '\0', mn->i + 1);
			}
			else if (mn->read < BUFF_SIZE)
				mn->read = 0;
		}
		else if (mn->buff[0])
			mn->read = mn->fd;
	}
	else if ((*out = get_l(line, f_n(mn->fd, NULL), 0, mn)) < 2 && mn->buff[0])
		mn->read = mn->fd;
	mn->i = 0;
}

int			get_next_line(const int fd, char **line)
{
	static t_gnl	*lst;
	t_gnl			*master;
	int				out;

	if (!line || fd < 0)
		return (-1);
	master = fd_node_get(fd, &lst);
	get_master(line, master, &out);
	master->fd = fd;
	return (out);
}
