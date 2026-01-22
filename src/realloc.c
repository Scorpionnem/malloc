/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 16:57:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/22 14:01:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

static void	dumb_compiler(void *ptr)
{
	free(ptr);
}

void	*realloc(void *ptr, size_t size)
{
	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	t_block	*block = find_block_by_adress_global(ptr);
	if (!block)
		return (NULL);
	void	*blk = (void*)block + BLOCK_HEADER_SIZE;
	void	*res = malloc(size);
	if (!res)
		return (NULL);
	size_t	move_size = block->used_size > size ? size : block->used_size;
	memmove(res, blk, move_size);
	dumb_compiler(blk);
	return (res);
}
