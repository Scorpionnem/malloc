/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:09:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 14:32:45 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

/*
	mmap zones that will dispatch blocks.

	when you call malloc, it will "assign a zone" size to the call.

	From it, it will find an available zone, if it cant, it allocates a new one of appropriate size.

	then in the found zone it tries to find a block thats not used and thats >= the asked size
	if it cant find the block, it adds it to the zone

	large zones can probably just be a list of blocks instead of list of zones since the zone will only fit 1 block

	to free, just set the used flag to false

	if all blocks in the zone are unused, munmap?

	zone                                                   V .blocks points here
	-> [[size][adress to first block][adress to next zone][blocks]]

	block
	-> [[size][adress to block of memory][used state][adress to next block]]
	size is the total size of the zone counting the t_zone

	Each zone must contain at least 100 blocks

	sizeof(t_zone) = 24
	sizeof(t_block) = 32

*/

t_malloc	g_malloc = {0};

/*
	Finds/Allocate a zone

	@param zone zone group to find an available zone in
	@param size size of the user's allocation

	@return pointer to the adress of the created/found node or NULL on failure
*/
t_zone	**find_available_zone(t_zone **zone, size_t size)
{
	if (!*zone)
	{
		*zone = new_zone(size); // Initialize NULL zone
		if (!*zone)
			return (NULL);
		return (zone);
	}
	t_zone	**tmp_zone = zone;
	t_zone	**prev_tmp_zone = NULL;
	while ((*tmp_zone))
	{
		t_block	*tmp_block = (*tmp_zone)->blocks;

		while (tmp_block)
		{
			if (!tmp_block->used)
			{
				return (tmp_zone); // Zone is available
			}
			tmp_block = tmp_block->next;
		}
		prev_tmp_zone = tmp_zone;
		tmp_zone = &(*tmp_zone)->next;
	}
	(*prev_tmp_zone)->next = new_zone(size);
	if (!(*prev_tmp_zone)->next)
		return (NULL);
	return (&(*prev_tmp_zone)->next); // Append new zone to list
}

/*
	Returns the right zone group for size

	@param size size of the user's allocation

	@return pointer to the adress to the first zone
*/
t_zone	**get_zone(size_t size)
{
	if (size <= SMALL_ALLOC_SIZE)
		return (&g_malloc.small_zones);
	if (size <= MEDIUM_ALLOC_SIZE)
		return (&g_malloc.medium_zones);
	return (&g_malloc.large_zones);
}

void	*ft_malloc(size_t size)
{
	t_zone	**zone = get_zone(size);
	zone = find_available_zone(zone, size);
	if (!*zone)
		return (NULL);

	t_block	*res = find_block(*zone, size);
	if (!res) // If this happens, wtf?!
		return (NULL);
	res->used = true;
	return (res->adress);
}

int	main(void)
{
	ft_malloc(16);
	ft_malloc(16);
	ft_malloc(64);
	ft_malloc(500);
	ft_malloc(420);

	print_zones("SMALL", g_malloc.small_zones);
	printf("\n");
	print_zones("MEDIUM", g_malloc.medium_zones);
	printf("\n");
	print_zones("LARGE", g_malloc.large_zones);
}
