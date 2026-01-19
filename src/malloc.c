/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:42:04 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/19 14:48:43 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

t_malloc	g_malloc = {0};

/*
	Finds/Allocate a zone

	@param zone zone group to find an available zone in
	@param size size of the user's allocation

	@return pointer to the adress of the created/found node or NULL on failure
*/
static t_zone	**find_available_zone(t_zone **zone, size_t size)
{
	if (!*zone)
	{
		*zone = new_zone(size); // Initialize NULL zone
		if (!*zone)
			return (NULL);
		return (zone);
	}
	t_zone	**tmp_zone = zone;
	t_zone	**prev_tmp_zone = NULL;
	while ((*tmp_zone))
	{
		t_block	*tmp_block = (*tmp_zone)->blocks;

		while (tmp_block)
		{
			if (!tmp_block->used)
			{
				return (tmp_zone); // Zone is available
			}
			tmp_block = tmp_block->next;
		}
		prev_tmp_zone = tmp_zone;
		tmp_zone = &(*tmp_zone)->next;
	}
	(*prev_tmp_zone)->next = new_zone(size);
	if (!(*prev_tmp_zone)->next)
		return (NULL);
	return (&(*prev_tmp_zone)->next); // Append new zone to list
}

/*
	Returns the right zone group for size

	@param size size of the user's allocation

	@return pointer to the adress to the first zone
*/
static t_zone	**get_zone(size_t size)
{
	if (size <= SMALL_ALLOC_SIZE)
		return (&g_malloc.small_zones);
	if (size <= MEDIUM_ALLOC_SIZE)
		return (&g_malloc.medium_zones);
	return (&g_malloc.large_zones);
}

void	*ft_malloc(size_t size)
{
	t_zone	**zone = get_zone(size);
	zone = find_available_zone(zone, size);
	if (!*zone)
		return (NULL);

	t_block	*res = find_block(*zone, size);
	if (!res) // If this happens, wtf?!
		return (NULL);
	res->used = true;
	return (res->adress);
}
