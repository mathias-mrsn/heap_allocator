/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:21 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 00:32:50 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "slot.h"
#include "bucket.h"
#include "free_internal.h"

void *
new_slot(
    bucket  *bucket,
    const size_t  size)
{
    slot *slot = bucket->last;

    if (bucket->zone == LARGE) {
        return (bucket->ptr);
    } else {
        slot->next = (void *)slot + size + SIZEOF_SLOT;
        slot->state = USED;    
        bucket->last = slot->next; 
    }
    
    return ((void *)slot + SIZEOF_SLOT);
}

//! TODO: I have to test this function, I wrote it in 5 minutes.

void *
insert_slot (
    bucket* b,
    slot*   s,
    const size_t  size)
{
    const size_type size_free = compute_slot_size(s);
    const size_type type = GET_TYPE_BELOW(b->zone);
    slot*           save;

    if (size_free - size > type + SIZEOF_SLOT) {
        save = s->next;
        s->next = (void *)s + size + SIZEOF_SLOT;
        s->next->state = FREE;
        s->next->next = save;
        s->state = USED;
        MALLOC_DEBUG("malloc: insert_slot(): split slot");
    } else {
        s->state = USED;
        MALLOC_DEBUG("malloc: insert_slot(): use old slot");
    }
    
    return ((void *)s + SIZEOF_SLOT);
}

INLINE
size_type
compute_slot_size (
    const slot * s )
{
    return ((void*)s->next - ((void *)s + SIZEOF_SLOT));
}

int
free_slot (
    bucket * b,
    const void * ptr )
{
    if (b->zone == LARGE) {
        destroy_bucket(b);
        if (ptr != (void *)b + SIZEOF_BUCKET) {
            return (MIDDLE_OF_SLOT);
        }
        return (SUCCESS);
    } else {
        FOREACH_SLOT(b, s) {
            if ((ptr >= (void *)s && ptr < (void *)s->next)) {
                if (s->state & FREED) {
                    return (DOUBLE_FREE);
                }
                if (s->state & FREE) {
                    return (FREE_UNALLOCATED);
                }
                s->state = FREED;
                MALLOC_DEBUG("free: slot freed");
                if (ptr != (void *)s + SIZEOF_SLOT) {
                    return (MIDDLE_OF_SLOT);
                }
                
                return (SUCCESS);
            }
        }
    }
    MALLOC_DEBUG("free: slot not found");
    return (INVALID_POINTER);
}