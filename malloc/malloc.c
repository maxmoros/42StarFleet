/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:48:55 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/28 21:10:05 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

g_page_header	*g_pages[3] = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex[3] = {
				PTHREAD_MUTEX_INITIALIZER,
				PTHREAD_MUTEX_INITIALIZER,
				PTHREAD_MUTEX_INITIALIZER};

size_t			page_size(int shape, size_t size)
{
	if (!shape)
		return (sizeof(t_page_header) + size);
	return (shape == 1 ? PAGESIZE(LARGE) : PAGESIZE(TINY)); //Can be compressed?
}

t_page_header	*init_page(t_page_header *prev, int shape, size_t size)
{
	
}

t_page_header	*get_page(size_t size, int *shape)
{
	if (size <= TINY)
		*shape = 2;
	else
		*shape = (size <= LARGE ? 1 : 0);
	if (!g_pages[*shape])
		g_pages[*shape] = init_page(NULL, *shape, size);
	return (g_pages[*shape]);
}

void			add_block(t_page_header *page, t_block_header *block,
							int size)
{
	t_block_header	*new_block;

	block->used = 1;
	if (block->len - size < BLOCK_SIZE(1))
	{
		block->buff = block->len - size;
		return ;
	}
	new_block = (t_block_header*)(block + BLOCK_SIZE(size));
	new_block->len = block->len - BLOCK_SIZE(size);
	block->len = size;		//location??
	new_block->buff = 0;
	new_block->used = 0;
	new_block->page = page;
}

t_block_header	*get_block(t_page_header *page, int shape, size_t size)
{
	t_block_header	*block;

	block = (t_block_header*)(page + sizeof(t_page_header));
	while (block < page + page->size - page->leftover
			&& (block->used || block->len < size))
		block = (t_block_header*)(block + BLOCK_SIZE(block->len));
	if (block < page + page->size - page->leftover)
	{
		if (block + BLOCK_SIZE(block->len) == page + page->size)
			page->leftover -= BLOCK_SIZE(size);		//Last Block
		add_block(page, block, size);
		return (block);
	}
	page->next = init_page(page, shape, size);
	return (get_block(page->next, shape, size));
}

void			*malloc(size_t size)
{
	t_page_header	*page;
	t_block_header	*block;
	int				shape;

	if (size <= 0)
		return (NULL);
	if (!(page = get_page(size, &shape)))
		return (NULL);
	if (!(block = get_block(page, shape, size)))
		return (NULL);
	return ((void*)(block + sizeof(t_block_header));
}

int				main()
{
	char	*map;

	map = mmap(NULL, 4096, PROT_ALL, MAP_FLAGS, -1, 0);
	map = "YOLO\n";
	ft_putstr(map);
	ft_puthex((int)map);
	return (0);
}
