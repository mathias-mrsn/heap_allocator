/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 18:29:30 by mamaurai         ###   ########.fr       */
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
    
        PUTSTR("FREE: trouveeeeeeeeeeeee");
    bucket * b = find(ptr);
    if (b == NULL) {
        ERROR("free(): invalid pointer");
        THREAD_SAFETY(unlock);
        return ;
    }
    if (b->zone == LARGE) {
        unlink_bucket(b);
        destroy_bucket(b);
        THREAD_SAFETY(unlock);
        return ;
    }
    const int ret = free_slot(b, ptr);
    switch (ret) {
        case INVALID_POINTER:
            ERROR("free(): invalid pointer\n");
            break;
        case MIDDLE_OF_SLOT:
            WARNING("free(): this pointer isn't at the begin of a slot; the entire slot has been freed\n");
            break;
        case DOUBLE_FREE:
            WARNING("free(): double free\n");
            break;
    }
    THREAD_SAFETY(unlock);
}
