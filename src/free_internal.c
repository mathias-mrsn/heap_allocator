/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/30 13:16:53 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include "slot.h"
#include "thread_safety.h"
#include <assert.h>
#include "free_internal.h"

INLINE
void
free_internal (
    void * ptr )
{
    THREAD_SAFETY(lock);
    
    bucket * b = find(ptr);
    if (b == NULL) {
        ERROR("free(): invalid pointer");
        THREAD_SAFETY(unlock);
        return ;
    }
    const int ret = free_slot(b, ptr);
    switch (ret) {
        case INVALID_POINTER:
            WARNING("free(): invalid pointer");
            break;
        case MIDDLE_OF_SLOT:
            WARNING("free(): this pointer isn't at the begin of a slot; the entire slot has been freed");
            break;
        case DOUBLE_FREE:
            WARNING("free(): double free");
            break;
        case FREE_UNALLOCATED:
            WARNING("free(): free unallocated");
            break;
    }
    THREAD_SAFETY(unlock);

#if (ABORT_IF_ERROR == 1)
    assert(ret == 0);
#endif
}
