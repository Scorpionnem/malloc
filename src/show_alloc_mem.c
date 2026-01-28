/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:56:39 by mbatty            #+#    #+#             */
/*   Updated: 2026/01/28 11:24:58 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

# define NIL_STR		"(nil)"
# define LOWER_HEX		"0123456789abcdef"
# define NULL_STRING	"(null)"

static int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

static int	ft_putstr(char *str)
{
	if (!str)
		return (ft_putstr(NULL_STRING));
	return (write(1, str, ft_strlen(str)));
}

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

static int	ft_putnbr(long n)
{
	if (n < 0)
		return (write(1, "-", 1) + ft_putnbr(n * -1));
	if (n >= 0 && n <= 9)
		return (ft_putchar(n % 10 + '0'));
	return (ft_putnbr(n / 10) + ft_putnbr(n % 10));
}

static int	ft_putnbr_hex_u(unsigned long int n, char *set)
{
	if (n <= 15)
		return (ft_putchar(set[n % 16]));
	return (ft_putnbr_hex_u(n / 16, set) + ft_putnbr_hex_u(n % 16, set));
}

static int	ft_putadress(void *n)
{
	if (n == 0)
		return (ft_putstr(NIL_STR));
	return (ft_putstr("0x") + ft_putnbr_hex_u((unsigned long int)n, LOWER_HEX));
}

static void	print_blocks(t_block *block)
{
	while (block)
	{
		void	*addr = (void*)block + BLOCK_HEADER_SIZE;
		if (block->used_size > 0)
		{
			ft_putadress(addr);
			ft_putstr(" - ");
			ft_putadress(addr + block->used_size);
			ft_putstr(" : ");
			ft_putnbr(block->used_size);
			ft_putstr(" bytes\n");
		}
		block = block->next;
	}
}

static void	print_zone(char *zone_type, t_zone *zone)
{
	while (zone)
	{
		void	*addr = (void*)zone + ZONE_HEADER_SIZE;
		ft_putstr(zone_type);
		ft_putadress(addr);
		ft_putchar('\n');
		print_blocks(zone->blocks);
		zone = zone->next;
	}
}

void show_alloc_mem(void)
{
	pthread_mutex_lock(&g_malloc.mutex);
	print_zone("TINY ZONES: ", g_malloc.small_zones);
	print_zone("SMALL ZONES: ", g_malloc.medium_zones);
	print_zone("LARGE ZONES: ", g_malloc.large_zones);
	pthread_mutex_unlock(&g_malloc.mutex);
}
