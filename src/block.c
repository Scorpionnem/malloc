/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:29:06 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 12:46:44 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

/*
	Finds a block of at least size inside of given zone

	@param zone zone to find the block in
	@param size minimum size of block to return

	@return adress of valid block if found, otherwise NULL
*/
t_block	*find_block(t_zone *zone, size_t size)
{
	t_block	*tmp = zone->blocks;

	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!tmp->used && tmp->size >= size)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_block	*new_block(t_block *addr, size_t size)
{
	t_block	*res = addr;

	res->size = size;
	res->adress = (void*)(res + sizeof(t_block));
	res->next = NULL;
	res->used = false;
	return (res);
}

/*
	Finds the last block in the list of blocks inside of given zone

	@param zone zone to traverse

	@return returns the last block, NULL if no blocks exist in that zone
*/
t_block	*get_last_block(t_zone *zone)
{
	t_block	*it = zone->blocks;
	
	if (!it)
		return (NULL);
	while (it->next)
		it = it->next;
	return (it);
}

/*
	Adds a new block of given size to the zone

	@param zone in wich to add new block
	@param size size of the block

	@return adress of new block on success, NULL on failure
*/
t_block	*add_block_to_zone(t_zone *zone, size_t size)
{
	t_block	**tmp;

	tmp = &zone->blocks;
	if (!*tmp)
	{
		(*tmp) = (void*)((uint8_t*)zone + sizeof(t_zone));
		return (new_block(*tmp, size));
	}

	t_block	*it = get_last_block(zone);

	t_block	*next_adress = (void*)((uint8_t*)it + sizeof(t_block) + it->size);

	t_block *res = new_block(next_adress, size);

	it->next = res;
	return (res);
}
