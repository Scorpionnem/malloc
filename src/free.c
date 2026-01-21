/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:09:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/21 17:39:11 by mbatty           ###   ########.fr       */
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

static void	free_zone(t_zone **zone)
{
	if (!*zone)
		return ;

	t_zone	*it = *zone;
	t_zone	*prev = NULL;
	t_zone	*next = it->next;

	while (it)
	{
		next = it->next;
		if (!is_zone_used(it))
		{
			munmap(it, it->size);
			if (prev)
				prev->next = next;
			else
				*zone = next;
			break ;
		}
		prev = it;
		it = next;
	}
}

static void	free_unused_zones()
{
	free_zone(&g_malloc.small_zones);
	free_zone(&g_malloc.medium_zones);
	free_zone(&g_malloc.large_zones);
}

#define INVALID_FREE_STR "free(): invalid pointer\nrealloc(): invalid pointer\n"

void	free(void *ptr)
{
	t_block	*block = find_block_by_adress_global(ptr);
	if (!block || !block->used)
	{
		write(2, INVALID_FREE_STR, sizeof(INVALID_FREE_STR));
		return ;
	}

	block->used = false;
	free_unused_zones();
}
