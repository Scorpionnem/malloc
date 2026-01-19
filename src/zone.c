/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:29:00 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 13:13:01 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

t_zone	*new_zone(size_t size)
{
	(void)size;
	t_zone	*res;
	size_t page_size = sysconf(_SC_PAGESIZE);
	size_t	caca_size = 1;

	res = mmap(NULL, caca_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
	if (res == MAP_FAILED)
		return (NULL);
	res->size = caca_size * page_size;
	res->next = NULL;
	res->blocks = NULL;

	#define BLOCKS 16
	for (int i = 0; i < BLOCKS; i++) // Precreate all the blocks in the zone, all set to unused
		add_block_to_zone(res, 32);

	return (res);
}
