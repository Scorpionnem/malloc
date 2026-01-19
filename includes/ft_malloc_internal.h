/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:09 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 22:50:21 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include "ft_malloc.h"

# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

# include <sys/mman.h>

# include <stdio.h>

typedef struct	s_block
{
	size_t	size;
	void	*adress;
	bool	used;

	struct s_block	*next;
}	t_block;

typedef struct	s_zone
{
	size_t	size;
	t_block	*blocks;

	struct s_zone	*next;
}	t_zone;

typedef struct	s_malloc
{
	t_zone	*small_zones;
	t_zone	*medium_zones;
	t_zone	*large_zones;
}	t_malloc;

/*
	Macro used to align the memory, for example in the header of memory blocks:

	size_t header_size = ALIGN_UP(sizeof(t_block), alignof(max_align_t));

	header_size % alignof(max_align_t) == 0
	for memory to be aligned this needs to be true
*/
#define ALIGN_MEMORY(x, a) (((x) + ((a) - 1)) & ~((a) - 1))

extern t_malloc	g_malloc;

// 127 blocks of 64 (allocs of 32)
#define SMALL_ALLOC_SIZE 96
#define SMALL_BLOCKS_COUNT 1024
#define SMALL_PAGES 4

// 127 blocks of 128 (allocs of 96)
#define MEDIUM_ALLOC_SIZE 992
#define MEDIUM_BLOCKS_COUNT 1024
#define MEDIUM_PAGES 32

void	print_blocks(t_block *block);
void	print_zones(char *id, t_zone *zone);

t_block	*find_block(t_zone *zone, size_t size);
t_block	*add_block_to_zone(t_zone *zone, size_t size);

t_zone	*new_zone(size_t size);

#endif
