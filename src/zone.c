/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:29:00 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 13:57:00 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

size_t	get_pages_count(size_t size)
{
	if (size <= SMALL_ALLOC_SIZE)
		return (SMALL_PAGES);
	if (size <= MEDIUM_ALLOC_SIZE)
		return (MEDIUM_PAGES);
		
	size_t page_size = sysconf(_SC_PAGESIZE);

	return (size / page_size + 1);
}

size_t	get_blocks_size(size_t size)
{
	if (size <= SMALL_ALLOC_SIZE)
		return (SMALL_ALLOC_SIZE);
	if (size <= MEDIUM_ALLOC_SIZE)
		return (MEDIUM_ALLOC_SIZE);
	return (size);
}

size_t	get_blocks_count(size_t size)
{
	if (size <= SMALL_ALLOC_SIZE)
		return (SMALL_BLOCKS_COUNT);
	if (size <= MEDIUM_ALLOC_SIZE)
		return (MEDIUM_BLOCKS_COUNT);
	return (1);
}

t_zone	*new_zone(size_t size)
{
	size_t page_size = sysconf(_SC_PAGESIZE);
	
	size_t	pages = get_pages_count(size);
	size_t	blocks_count = get_blocks_count(size);
	size_t	blocks_size = get_blocks_size(size);

	t_zone	*res;

	res = mmap(NULL, pages * page_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (res == MAP_FAILED)
		return (NULL);
	res->size = pages * page_size;
	res->next = NULL;
	res->blocks = NULL;

	for (size_t i = 0; i < blocks_count; i++) // Precreate all the blocks in the zone, all set to unused
		add_block_to_zone(res, blocks_size);

	return (res);
}
