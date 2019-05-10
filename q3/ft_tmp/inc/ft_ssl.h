/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 11:08:19 by mmoros            #+#    #+#             */
/*   Updated: 2019/05/09 19:01:56 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>		//#############
# include <ft_md5.h>

# define FLAG_P	0x01
# define FLAG_Q	0x02
# define FLAG_R	0x04
# define FLAG_S	0x08

# define BUF_SIZE 64

typedef struct		s_512chunk
{
	uint32_t		c[16];
}					t_512chunk;

typedef struct		s_ft_ssl
{
	char			flags;
	void			(*hash)();
	char			debug;
}					t_ft_ssl;

extern char			buf[BUF_SIZE];
extern t_ft_ssl		g_ft_ssl;

int					set_hash(char *hash);
int					set_flags(int *argc, char ***args);

void				md5(t_512chunk *chunk);
void				init_md5();
void				sha256(t_512chunk *chunk);
void				init_sha256();

void				read_fd(int fd);
void				read_file(char *path);
void				read_str(char *str);

void				push_chunk();
void				print_chunk(uint32_t *table);
void				flip_chunk();

#endif
