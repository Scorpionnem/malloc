/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:29:57 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 13:56:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	print_blocks(t_block *block)
{
	printf("BLOCK: %p SIZE: %ld USED: %d\n", block, block->size, block->used);
	for (size_t i = 0; i < block->size; i++)
		printf("%x ", *(uint8_t*)(block->adress + i));
	printf("\n");
	if (block->next && block->next->used)
		print_blocks(block->next);
}

void	print_zones(char *id, t_zone *zone)
{
	if (!zone)
		return ;
	printf("%s ZONE: %p SIZE: %ld\n", id, zone, zone->size);
	if (zone->blocks)
		print_blocks(zone->blocks);
	if (zone->next)
		print_zones(id, zone->next);
}
