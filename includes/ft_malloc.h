/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 01:56:29 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 15:27:33 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

/*
	zone:
		Zone is the memory that is actually mapped, it stores a list of blocks.
		A list of zones for each size is stored in the global state

		-> [[size][adress to first block][adress to next zone][blocks]]
		-> size: size of the usable memory
		-> blocks: adress to the first block
		-> next: next zone

	block:
		Blocks store the adresses that are returned to the user aswell as the size of the zones

		-> [[size] [adress to block of memory] [used state] [adress to next block]]
	
		-> size: size of the usable memory
		-> adress: adress of the start of the usable memory
		-> used: is the block used?
		-> next: next block
*/

# include <stddef.h>

void	*malloc(size_t size);
void	free(void *addr);

#endif
