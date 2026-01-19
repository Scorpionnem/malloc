/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:28:09 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 12:54:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include "ft_malloc.h"

# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

# include <sys/mman.h>

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
	t_zone	*tiny_zones;
	t_zone	*small_zones;
	t_zone	*large_zones;
}	t_malloc;

typedef enum	e_zone_size
{
	ZONE_TINY,
	ZONE_SMALL,
	ZONE_LARGE
}	t_zone_size;

typedef enum	e_block_size
{
	BLOCK_TINY,
	BLOCK_SMALL,
	BLOCK_LARGE
}	t_block_size;

void	print_blocks(t_block *block);
void	print_zones(t_zone *zone);

t_block	*find_block(t_zone *zone, size_t size);
t_block	*add_block_to_zone(t_zone *zone, size_t size);

t_zone	*new_zone(size_t size);

#endif
