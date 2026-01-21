/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:06:24 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/21 15:08:54 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	create_blocks_in_zone(t_zone *zone, size_t blocks_size, size_t blocks_count);
t_zone	*allocate_zone(size_t blocks_size, size_t blocks_count);
bool	is_zone_used(t_zone *zone);

/*
	Allocates a zone. It calculates the number of pages to allocate (It counts the size of the zone and blocks headers)

	@param blocks_size size of the blocks to fit in the zone
	@param blocks_count number of blocks to fit in the zone
*/
t_zone	*allocate_zone(size_t blocks_size, size_t blocks_count)
{
	t_zone	*res;
	size_t	pages = get_zone_pages(blocks_size, blocks_count);

	printf("Mapping: %zu pages (%zu) ", pages, pages * PAGE_SIZE);
	printf("to store %zu blocks of size %zu (%zu)\n", blocks_count, blocks_size, blocks_count * blocks_size);

	res = mmap(NULL, pages * PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (res == MAP_FAILED)
		return (NULL);
	memset(res, 0, sizeof(t_zone));

	res->size = blocks_size * blocks_count;
	create_blocks_in_zone(res, blocks_size, blocks_count);
	return (res);
}

/*
	Creates blocks_count blocks inside of the zone

	@param zone zone where the blocks will be created
	@param blocks_size size of the blocks to create
	@param blocks_count number of blocks to create
*/
void	create_blocks_in_zone(t_zone *zone, size_t blocks_size, size_t blocks_count)
{
	(void)zone;(void)blocks_size;(void)blocks_count;

	zone->blocks = (void*)zone + ZONE_HEADER_SIZE;
	memset(zone->blocks, 0, sizeof(t_block));
	zone->blocks->size = blocks_size;

	t_block	*prev = zone->blocks;
	t_block	*tmp = (void*)prev + BLOCK_HEADER_SIZE + prev->size;
	size_t	i = 0;
	while (i < blocks_count - 1)
	{
		prev->next = tmp;

		memset(tmp, 0, sizeof(t_block));
		tmp->size = blocks_size;

		prev = tmp;
		tmp = (void*)prev + BLOCK_HEADER_SIZE + prev->size;
		i++;
	}
}

/*
	Checks if at least one block in zone is used
*/
bool	is_zone_used(t_zone *zone)
{
	t_block	*it = zone->blocks;

	while (it)
	{
		if (it->used)
			return (true);
		it = it->next;
	}
	return (false);
}
