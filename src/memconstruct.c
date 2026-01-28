/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memconstruct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:34:54 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 12:37:16 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	*locked_memconstruct(size_t size, void *ptr)
{
	void	*res = locked_malloc(size);
	if (!res)
		return (NULL);
	ft_memcpy(res, ptr, size);
	return(res);
}

void	*memconstruct(size_t size, void *ptr)
{
	pthread_mutex_lock(&g_malloc.mutex);
	void	*res = locked_memconstruct(size, ptr);
	pthread_mutex_unlock(&g_malloc.mutex);
	return (res);
}
