/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:56:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 01:59:24 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdbool.h>
# include <stdint.h>
# include <unistd.h>

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
	TINY,
	SMALL,
	LARGE
}	t_zone_size;

#endif
