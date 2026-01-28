/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:57:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 11:31:28 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	*locked_realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (locked_malloc(size));
	if (size == 0)
	{
		locked_free(ptr);
		return (NULL);
	}

	t_block	*block = find_block_by_adress_global(ptr);
	if (!block)
		return (NULL);
	void	*blk = (void*)block + BLOCK_HEADER_SIZE;
	void	*res = locked_malloc(size);
	if (!res)
		return (NULL);
	size_t	move_size = block->used_size > size ? size : block->used_size;
	ft_memmove(res, blk, move_size);
	locked_free(blk);
	return (res);
}

void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_malloc.mutex);
	void	*res = locked_realloc(ptr, size);
	pthread_mutex_unlock(&g_malloc.mutex);
	return (res);
}
