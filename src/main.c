/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:09:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 13:13:22 by mbatty           ###   ########.fr       */
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
*/

t_zone	*zone = NULL;

void	*ft_malloc(size_t size)
{
	if (!zone)
	{
		zone = new_zone(1);
		if (!zone)
			return (NULL);
	}

	t_block	*res = find_block(zone, size);
	if (!res)
		return (NULL);
	res->used = true;
	return (res->adress);
}

#include <stdio.h>

int	main(void)
{
	printf("PageSize %ld Zone size %ld Block size %ld\n", sysconf(_SC_PAGESIZE), sizeof(t_zone), sizeof(t_block));
	char	*caca = ft_malloc(16);

	caca[0] = 'c';
	caca[1] = 'a';
	caca[2] = 'c';
	caca[3] = 'a';

	print_zones(zone);

	munmap(zone, zone->size);
}
