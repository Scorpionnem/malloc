/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:47:35 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 15:03:05 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

static t_block	*find_block_in_zone(t_zone *zone, void *addr)
{
	while (zone)
	{
		t_block	*tmp = zone->blocks;
		while (tmp)
		{
			if (tmp->adress == addr)
				return (tmp);
			tmp = tmp->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

/*
	Returns the first block found that has the same address as addr
*/
static t_block	*find_block_addr(void *addr)
{
	t_block	*res = find_block_in_zone(g_malloc.small_zones, addr);
	if (res)
		return (res);
	res = find_block_in_zone(g_malloc.medium_zones, addr);
	if (res)
		return (res);
	res = find_block_in_zone(g_malloc.large_zones, addr);
	if (res)
		return (res);
	printf("INVALID FREE\n");
	return (NULL);
}

void	ft_free(void *addr)
{
	if (!addr)
		return ;
	
	t_block	*block = find_block_addr(addr);
	if (!block)
		return ;
	
	if (!block->used)
		printf("DOUBLE FREE\n");
	block->used = false; // Then check if zone should be freed, if so link things back together and all
}
