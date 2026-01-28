/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:42:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 11:29:06 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

t_malloc	g_malloc = {0};

void	append_zone(t_zone **zone, t_zone *new_zone)
{
	if (!*zone)
	{
		*zone = new_zone;
		return ;
	}

	t_zone	*it = *zone;
	while (it->next)
		it = it->next;

	new_zone->prev = it;
	it->next = new_zone;
}

void	*locked_malloc(size_t size)
{
	t_zone	**zone;

	if (size <= SMALL_ALLOC_SIZE)
		zone = &g_malloc.small_zones;
	else if (size <= MEDIUM_ALLOC_SIZE)
		zone = &g_malloc.medium_zones;
	else
		zone = &g_malloc.large_zones;

	t_block	*block = find_unused_block_by_size(*zone, size);
	if (!block)
	{
		size_t	alloc = get_alloc_size(size);
		size_t	blocks = get_blocks_count(size);
		t_zone	*new_zone = allocate_zone(alloc, blocks);
		if (!new_zone) // NOOOO ALLOC FAIL BOZO
			return (NULL);

		new_zone->group = zone;
		append_zone(zone, new_zone);

		block = find_unused_block_by_size(*zone, size);
	}
	block->used = true;
	block->zone->used_blocks++;
	block->used_size = size;
	return ((void*)block + BLOCK_HEADER_SIZE);
}

void	*malloc(size_t size)
{
	pthread_mutex_lock(&g_malloc.mutex);
	void	*res = locked_malloc(size);
	pthread_mutex_unlock(&g_malloc.mutex);
	return (res);
}
