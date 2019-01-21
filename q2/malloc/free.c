/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 20:02:12 by mmoros            #+#    #+#             */
/*   Updated: 2018/07/29 21:57:19 by mmoros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_block(/*t_page_header *page,*/ t_block_header *block)
{
//	if (page)
//		;
	printf("\tB\n");
	block->used = 0;
	printf("\tC\n");
	block->len += block->buff;
	printf("\tD\n");
	block->buff = 0;
	printf("\tE\n");
//	bzero(block + sizeof(t_block_header), block->len);
}

void	free(void *ptr)
{
	t_page_header	*page;
	t_block_header	*block;

	printf("free attempt\n");
	block = (t_block_header*)(ptr - sizeof(t_block_header));
	page = block->page;
	printf("\tA\n");
	printf("block len is %zu\n", block->len);
	pthread_mutex_lock(&g_mutex[page->shape]);
	free_block(/*page, */block);
	printf("freed\n");
	pthread_mutex_unlock(&g_mutex[page->shape]);
}
