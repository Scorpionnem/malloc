/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:43:12 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 12:54:35 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

void	*calloc(size_t size)
{
	void	*res = malloc(size);
	if (!res)
		return (NULL);
	return (ft_memset(res, 0, size));
}
