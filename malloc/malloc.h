/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:52:35 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/28 19:44:50 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <pthread.h>
# include <sys/mman.h>

# define BLOCK_PER_PAGE 256
# define TINY 128
# define LARGE 2048
# define BLOCK_SIZE(x)	(x + sizeof(t_block_header))
# define PAGE_SIZE(x)	(sizeof(t_page_header) + BLOCK_SIZE(x) * BLOCK_PER_PAGE)
# define INIT_MEM(x)	(PAGE_SIZE(x) - sizeof(t_page_header) - BLOCK_SIZE(0))
# define PROT_ALL		(PROT_READ | PROT_WRITE | PROT_EXEC)
# define MAP_FLAGS		(MAP_ANONYMOUS | MAP_PRIVATE | MAP_NOCACHE)
# define NEXT_BLOCK(x)	((void*)x + x->len + sizeof(t_block_header))
	//Make sure x comes in as t_header


void						*malloc(size_t size);

typedef struct				s_page_header
{
	struct s_page_header	*next;
	uint8_t					shape:2;
	uint8_t					used:1;
	size_t					size;
	size_t					leftover;
}							t_page_header;

typedef struct				s_block_header
{
	size_t					len;
	char					buff;
	uint8_t					used:1;
	struct s_page_header	*page;
}							t_block_header;

extern t_page_header		*g_pages[3];
extern pthread_mutex_t		g_mutex[3];

#endif

