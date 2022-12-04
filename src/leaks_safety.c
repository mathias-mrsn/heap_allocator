/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_safety.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:10:31 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 13:15:58 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks_safety.h"
#include "commun.h"
#include "show_alloc_mem_internal.h"
#include <sys/mman.h>
#include "thread_safety.h"

PRIVATE
void
_clear_zone (
    const int zone_type )
{
    bucket *    current = memory[zone_type];
    size_type   size = 0;
    bucket *    del = NULL;

    while (current) {
        del = current;
        current = current->next;
        size = GET_SIZE(zone_type, del->size_allocated) + SIZEOF_BUCKET;
        if (munmap(del, size)) {
            MALLOC_DEBUG("malloc: munmap() failed\n")
            return;
        }
    }
}

# if (LEAK_SAFETY == 1)
DESTRUCTOR
#endif
void
leak_safety (void)
{
# if (LEAK_SAFETY == 0)
    THREAD_SAFETY(lock);
#endif
    
    show_alloc_mem_internal();
    _clear_zone(TINY);
    _clear_zone(SMALL);
    _clear_zone(LARGE);
    ft_memset(&memory, 0, sizeof(bucket *) * 6);    

# if (LEAK_SAFETY == 0)
    THREAD_SAFETY(unlock);
#endif
}