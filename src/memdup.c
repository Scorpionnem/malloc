/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:29:22 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 12:32:19 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	*locked_memdup(void *ptr)
{
	if (!ptr)
		return (NULL);

	t_block	*block = find_block_by_adress_global(ptr);
	if (!block)
		return (NULL);
	void	*addr = (void*)block + BLOCK_HEADER_SIZE;
	void	*res = locked_malloc(block->used_size);
	if (!res)
		return (NULL);
	ft_memcpy(res, addr, block->used_size);
	return (res);
}

void	*memdup(void *ptr)
{
	pthread_mutex_lock(&g_malloc.mutex);
	void	*res = locked_memdup(ptr);
	pthread_mutex_unlock(&g_malloc.mutex);
	return (res);
}
