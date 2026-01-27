/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:56:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/27 14:10:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

/*
	TINY : 0xA0000
	0xA0020 - 0xA004A : 42 bytes
	0xA006A - 0xA00BE : 84 bytes
	SMALL : 0xAD000
	0xAD020 - 0xADEAD : 3725 bytes
	LARGE : 0xB0000
	0xB0020 - 0xBBEEF : 48847 bytes
	Total : 52698 bytes
*/

static void	print_blocks(t_block *block)
{
	while (block)
	{
		void	*addr = (void*)block + BLOCK_HEADER_SIZE;
		if (block->used_size > 0)
			printf("%p - %p : %zu bytes\n", addr, addr + block->used_size, block->used_size);
		block = block->next;
	}
}

static void	print_zone(const char *zone_type, t_zone *zone)
{
	while (zone)
	{
		void	*addr = (void*)zone + ZONE_HEADER_SIZE;
		printf("%s %p\n", zone_type, addr);
		print_blocks(zone->blocks);
		zone = zone->next;
	}
}

void show_alloc_mem(void)
{
	print_zone("TINY ZONES:", g_malloc.small_zones);
	print_zone("SMALL ZONES:", g_malloc.medium_zones);
	print_zone("LARGE ZONES:", g_malloc.large_zones);
}
