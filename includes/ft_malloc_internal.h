/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:09 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/27 13:33:09 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include "ft_malloc.h"

# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>
# include <stddef.h>
# include <string.h>

# include <sys/mman.h>

# include <stdio.h>

int	ft_putnbr(long n);
int	ft_putchar(char c);

typedef struct	s_block
{
	size_t	size;

	size_t	used_size;
	bool	used;

	struct s_zone	*zone;

	struct s_block	*next;
}	t_block;

typedef struct	s_zone
{
	size_t	size;
	size_t	blocks_size;
	size_t	used_blocks;
	t_block	*blocks;

	struct s_zone	*prev;
	struct s_zone	*next;

	struct s_zone	**group;
}	t_zone;

typedef struct	s_malloc
{
	t_zone	*small_zones;
	t_zone	*medium_zones;
	t_zone	*large_zones;
}	t_malloc;

#define ALIGN_MEMORY(x, a) (((x) + ((a) - 1)) & ~((a) - 1))
#define ZONE_HEADER_SIZE ALIGN_MEMORY(sizeof(t_zone), 16)
#define BLOCK_HEADER_SIZE ALIGN_MEMORY(sizeof(t_block), 16)

extern t_malloc	g_malloc;

#define PAGE_SIZE sysconf(_SC_PAGESIZE)

#define SMALL_BLOCKS_COUNT 128
#define SMALL_ALLOC_SIZE 128

#define MEDIUM_BLOCKS_COUNT 128
#define MEDIUM_ALLOC_SIZE 1024

// zone.c
bool	is_zone_used(t_zone *zone);
t_zone	*allocate_zone(size_t blocks_size, size_t blocks_count);

// block.c
t_block	*find_block_by_adress(t_zone *zone, void *addr);
t_block	*find_unused_block_by_size(t_zone *zone, size_t size);

// utils.c
size_t	get_zone_pages(size_t blocks_size, size_t blocks_count);
size_t	get_alloc_size(size_t alloc_size);
size_t	get_blocks_count(size_t alloc_size);

t_block	*find_block_by_adress_global(void *addr);

#endif
