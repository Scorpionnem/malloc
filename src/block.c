/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:05:31 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/21 15:40:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

t_block	*find_unused_block_by_size(t_zone *zone, size_t size);
t_block	*find_block_by_adress(t_zone *zone, void *addr);

/*
	Find a block in given zone group thats unused and at least of size size

	@param zone zone group to find block in
	@param size size of block to fit
*/
t_block	*find_unused_block_by_size(t_zone *zone, size_t size)
{
	while (zone)
	{
		t_block	*it = zone->blocks;
	
		while (it)
		{
			if (it->size >= size && !it->used)
				return (it);
			it = it->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

/*
	Find a block in given zone group that has the same adress as addr

	@param zone zone group to find block in
	@param addr addr of block to find
*/
t_block	*find_block_by_adress(t_zone *zone, void *addr)
{
	while (zone)
	{
		t_block	*it = zone->blocks;
	
		while (it)
		{
			if ((void*)it == addr)
				return (it);
			it = it->next;
		}
		zone = zone->next;
	}
	return (NULL);
}
