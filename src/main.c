/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:09:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 02:00:27 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>

#include <stdio.h>

#include "ft_malloc.h"

void	print_blocks(t_block *block)
{
	printf("BLOCK: %p SIZE: %ld USED: %d\n", block, block->size, block->used);
	for (size_t i = 0; i < block->size; i++)
		printf("%d", *(uint8_t*)(block->adress + i));
	printf("\n");
	if (block->next)
		print_blocks(block->next);
}

void	print_zones(t_zone *zone)
{
	printf("ZONE: %p SIZE: %ld\n", zone, zone->size);
	if (zone->blocks)
		print_blocks(zone->blocks);
	if (zone->next)
		print_zones(zone->next);
}

t_block	*create_block(t_zone *zone, size_t size)
{
	t_block	**tmp;

	tmp = &zone->blocks;
	if (!*tmp)
	{
		(*tmp) = (void*)((uint8_t*)zone + sizeof(t_zone));

		t_block	*new_block = *tmp;

		new_block->size = size;
		new_block->adress = (void*)(new_block + sizeof(t_block));
		new_block->next = NULL;
		new_block->used = false;

		return (new_block);
	}

	t_block	*it = *tmp;

	while (it->next)
		it = it->next;

	t_block	*new_block = (void*)((uint8_t*)it + sizeof(t_block) + it->size);

	new_block->size = size;
	new_block->adress = (void*)(new_block + sizeof(t_block));
	new_block->next = NULL;
	new_block->used = false;

	it->next = new_block;
	return (new_block);
}

/*
	mmap zones that will dispatch blocks.

	zone                                                   V .blocks points here
	-> [[size][adress to first block][adress to next zone][blocks]]

	block
	-> [[size][adress to block of memory][used state][adress to next block]]
	size is the total size of the zone counting the t_zone
*/

int	main(void)
{
	t_zone	*test_zone = {0};

	size_t page_size = sysconf(_SC_PAGESIZE);
	test_zone = mmap(NULL, 1, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);

	test_zone->size = 1 * page_size;
	test_zone->next = NULL;

	create_block(test_zone, 16);
	create_block(test_zone, 16);
	create_block(test_zone, 16);
	create_block(test_zone, 16);

	print_zones(test_zone);

	munmap(test_zone, test_zone->size);
}
