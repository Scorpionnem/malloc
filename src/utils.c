/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:05:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/27 13:32:50 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

size_t	get_zone_pages(size_t blocks_size, size_t blocks_count);
size_t	get_alloc_size(size_t alloc_size);

/*
	Returns how many memory pages are needed for a zone with blocks_count blocks of blocks_size

	@param blocks_size size of the blocks
	@param blocks_count number of blocks in the zone

	@return returns number of pages to allocate
*/
size_t	get_zone_pages(size_t blocks_size, size_t blocks_count)
{
	return ((blocks_size * blocks_count + ZONE_HEADER_SIZE + blocks_count * BLOCK_HEADER_SIZE) / PAGE_SIZE + 1);
}

size_t	get_alloc_size(size_t alloc_size)
{
	if (alloc_size <= SMALL_ALLOC_SIZE)
		return (SMALL_ALLOC_SIZE);
	if (alloc_size <= MEDIUM_ALLOC_SIZE)
		return (MEDIUM_ALLOC_SIZE);
	return (alloc_size);
}

size_t	get_blocks_count(size_t alloc_size)
{
	if (alloc_size <= SMALL_ALLOC_SIZE)
		return (SMALL_BLOCKS_COUNT);
	if (alloc_size <= MEDIUM_ALLOC_SIZE)
		return (MEDIUM_BLOCKS_COUNT);
	return (1);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putnbr(long n)
{
	if (n < 0)
		return (write(1, "-", 1) + ft_putnbr(n * -1));
	if (n >= 0 && n <= 9)
		return (ft_putchar(n % 10 + '0'));
	return (ft_putnbr(n / 10) + ft_putnbr(n % 10));
}
