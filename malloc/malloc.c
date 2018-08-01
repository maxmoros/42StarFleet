/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:48:55 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/29 21:44:56 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_page_header	*g_pages[3] = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex[3] = {PTHREAD_MUTEX_INITIALIZER,
								PTHREAD_MUTEX_INITIALIZER,
								PTHREAD_MUTEX_INITIALIZER};

size_t			page_size(int shape, size_t size)
{
	static int	sys_page_size = 0;
	size_t		page_size;

	if (!sys_page_size)
		sys_page_size = getpagesize();
	if (!shape)
		page_size = (sizeof(t_page_header) + size);
	else
		page_size = (shape == 1 ? PAGE_SIZE(LARGE) : PAGE_SIZE(TINY));
	page_size += sys_page_size - page_size % sys_page_size;
	return (page_size);
}

t_page_header	*init_page(t_page_header *prev, int shape, size_t size)
{
	t_page_header	*page;
	t_block_header	*block;
	size_t			page_length;

	page_length = page_size(shape, size);
	if (!(page = (t_page_header*)mmap(NULL, page_length, PROT_ALL,
										MAP_FLAGS, -1, 0)))
		return (NULL);
	if (prev)
		prev->next = page;
	page->next = NULL;
	page->shape = shape;
	page->used = 0;
	page->size = page_length;
	page->leftover = INIT_MEM(page_length);
	block = FIRST_BLOCK(page);
	block->len = INIT_MEM(page_length);
	block->buff = 0;
	block->used = 0;
	block->page = page;
	return (page);
}

void			add_block(t_page_header *page, t_block_header *block, int size)
{
	t_block_header	*new_block;

	block->used = 1;
	if (block->len - size < BLOCK_SIZE(1))
	{
		block->buff = block->len - size;
		block->len = size;
		return ;
	}
	new_block = (t_block_header*)(block + BLOCK_SIZE(size));
	new_block->len = block->len - BLOCK_SIZE(size);
	block->len = size;
	new_block->buff = 0;
	new_block->used = 0;
	new_block->page = page;
}

t_block_header	*get_block(t_page_header *page, int shape, size_t size)
{
	t_block_header	*block;

	block = FIRST_BLOCK(page);
	while ((void*)block < (void*)END_USED_PAGE(page) && !BLOCK_FIT(block, size))
		block = NEXT_BLOCK(block);
	if ((void*)block < (void*)END_USED_PAGE(page))
	{
		if ((void*)NEXT_BLOCK(block) == (void*)END_OF_PAGE(page))
			page->leftover -= BLOCK_SIZE(size);
		add_block(page, block, size);
		return (block);
	}
	if (!page->next)
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
	if (size <= TINY)
		shape = 2;
	else
		shape = (size <= LARGE ? 1 : 0);
	pthread_mutex_lock(&g_mutex[shape]);
	if (!g_pages[shape] && !(g_pages[shape] = init_page(NULL, shape, size)))
	{
		pthread_mutex_unlock(&g_mutex[shape]);
		return (NULL);
	}
	page = g_pages[shape];
	if (!(block = get_block(page, shape, size)))
	{
		pthread_mutex_unlock(&g_mutex[shape]);
		return (NULL);
	}
	pthread_mutex_unlock(&g_mutex[shape]);
	return ((void*)(block + sizeof(t_block_header)));
}

int				main(void)
{
	char	*yolo1;
	char	*yolo2;
	char	*yolo3;
	char	*yolo4;

	yolo1 = malloc(6);
	yolo1 = "YOLO1\n";
	yolo2 = malloc(6);
	yolo2 = "YOLO2\n";
	yolo3 = malloc(6);
	yolo3 = "YOLO3\n";
	ft_putstr(yolo1);
	ft_puthex((int)yolo1);
	ft_putchar('\n');
	ft_putstr(yolo2);
	ft_puthex((int)yolo2);
	ft_putchar('\n');
	ft_putstr(yolo3);
	ft_puthex((int)yolo3);
	ft_putchar('\n');
	ft_putchar('\n');
	free(yolo2);
	yolo4 = malloc(6);
	printf("freed\n");
	yolo4 = "YOLO4\n";
	ft_putstr(yolo4);
	ft_puthex((int)yolo4);
	return (0);
}
