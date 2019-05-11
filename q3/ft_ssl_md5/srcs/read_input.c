/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:25:29 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/10 10:26:32 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

char	buf[BUF_SIZE];

char	append_one(char last)
{
	int		i;

	i = 1;
	while (!(last & 0x01 << i) && i < 16)
		i++;
	last |= 0x01 << (i - 1);
	return (last);
}

void	last_chunk(int left, size_t *length)
{
	buf[left++] = 0x80;
	ft_bzero(buf + left + 1, 64 - left - 1);
	*length *= 8;
	if (left < 57)
	{
		ft_memcpy(buf + 56, length, 8);
		push_chunk(1);
	}
	else
		push_chunk(0);
	if (left >= 57)
	{
		ft_bzero(buf, BUF_SIZE);
		ft_memcpy(buf + 56, length, 8);	
		push_chunk(1);
	}
}

void	read_str(char *str)
{
	int		full;
	int		left;
	size_t	length;
	int		i;

	ft_bzero(buf, BUF_SIZE);
	length = ft_strlen(str);
	full = length / 64;
	left = length % 64;
	i = -1;
	if (g_ft_ssl.debug)
		printf("read_str: full=%d, left=%d, length=%zu\n", full, left, length);
	while (++i < full)
	{
		ft_memcpy(buf, str + i * 64, 64);
		push_chunk(0);
	}
	ft_bzero(buf, BUF_SIZE);
	ft_memcpy(buf, str + 64 * full, left);
	last_chunk(left, &length);
}

void	read_fd(int fd)
{
	ssize_t		count;
	size_t		length;

	ft_bzero(buf, BUF_SIZE);
	length = 0;
	while ((count = read(fd, buf, BUF_SIZE)) == BUF_SIZE)
	{
		length += BUF_SIZE;
		push_chunk(0);
		ft_bzero(buf, BUF_SIZE);
	}
	length += count;
	last_chunk(count, &length);
}

void	read_file(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("ft_ssl: ");
		if (g_ft_ssl.hash == md5)
			ft_putstr("md5: ");
		else
			ft_putstr("sha256: ");
		ft_putstr(path);
		ft_putstr(": No such file or directory\n");
	}
	else
	{
		read_fd(fd);
		close(fd);
	}
}
