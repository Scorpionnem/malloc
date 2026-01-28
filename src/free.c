/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:09:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 12:52:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

/*
	Checks all zones in g_malloc to find where the block to free is
*/
t_block	*find_block_by_adress_global(void *addr)
{
	t_block	*res = find_block_by_adress(g_malloc.small_zones, addr);
	if (res)
		return (res);
	res = find_block_by_adress(g_malloc.medium_zones, addr);
	if (res)
		return (res);
	res = find_block_by_adress(g_malloc.large_zones, addr);
	if (res)
		return (res);
	return (NULL);
}

#define INVALID_FREE_STR "free(): invalid pointer\nrealloc(): invalid pointer\n"

void	locked_free(void *ptr)
{
	#if MALLOC_DEBUG
		ft_putstr("free called on adress ");
		ft_putadress(ptr);
		ft_putstr("\n");
	#endif
	if (!ptr)
		return ;
	t_block	*block = find_block_by_adress_global(ptr);
	if (!block || !block->used)
	{
		write(2, INVALID_FREE_STR, sizeof(INVALID_FREE_STR));
		return ;
	}

	block->used = false;
	block->zone->used_blocks--;
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_malloc.mutex);
	locked_free(ptr);
	pthread_mutex_unlock(&g_malloc.mutex);
}
