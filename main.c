/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:09:42 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 15:43:31 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_malloc_internal.h"

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

int	main(void)
{
	malloc(16);
	malloc(16);
	malloc(64);
	malloc(500);
	malloc(420);
}
