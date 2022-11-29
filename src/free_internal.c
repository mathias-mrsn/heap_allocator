/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/29 18:26:01 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include "slot.h"
#include "thread_safety.h"
#include <assert.h>

INLINE
void
free_internal (
    void * ptr )
{
    THREAD_SAFETY(lock);
    
    bucket * b = find(ptr);
    if (b == NULL) {
        ERROR("free(): invalid pointer");
        assert(0);
        THREAD_SAFETY(unlock);
        return ;
    }
    const int ret = free_slot(b, ptr);
    switch (ret) {
        case -1:
            ERROR("free(): invalid pointer");
            assert(0);
            break;
        case 1:
            WARNING("free(): this pointer isn't at the begin of a slot; the entire slot has been freed");
            break;
        default:
            break;
    }

    THREAD_SAFETY(unlock);
}
