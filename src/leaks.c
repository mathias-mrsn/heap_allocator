/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:10:31 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/23 17:29:09 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks.h"
#include "commun.h"
#include <sys/mman.h>

PRIVATE
void
_destroy_block (
    mem_block * del,
    int zone_type )
{
    const size_t size_del = (ZONE_TYPE_2_SIZE(zone_type) + BLOCK_SIZE);
    ft_memset(del, 0, size_del);
    if (munmap(del, size_del))
        LOG("malloc: munmap() failed\n")
}

PRIVATE
void
_clear_zone (
    int zone_type )
{
    mem_block * current = memory[zone_type][MEM_BEGIN];
    mem_block * del = NULL;

    while (current) {
        LOG("eop")
        del = current;
        current = current->next;
        _destroy_block(del, zone_type);
    }
}

DESTRUCTOR
void
leak_safety (void)
{
    _clear_zone(TINY);
    _clear_zone(MEDIUM);
    _clear_zone(LARGE);
    memory[TINY][MEM_BEGIN] = NULL;
    memory[TINY][MEM_END] = NULL;
    memory[MEDIUM][MEM_BEGIN] = NULL;
    memory[MEDIUM][MEM_END] = NULL;
    memory[LARGE][MEM_BEGIN] = NULL;
    memory[LARGE][MEM_END] = NULL;
    print_full_zone(TINY);
    print_full_zone(MEDIUM);
}