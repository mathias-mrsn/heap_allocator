/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:21 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/28 18:20:17 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "slot.h"
#include "bucket.h"

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

inline
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
   slot * s = b->ptr;

   for (; s != NULL && s->next != NULL; s = s->next) {
        if (s->state && (ptr >= (void *)s && ptr < (void *)s->next)) {
            s->state = FREE;
            MALLOC_DEBUG("free: slot freed");
            if (ptr != (void *)s + SIZEOF_SLOT) {
                return (1);
            }
            return (0);
        }
    }
    MALLOC_DEBUG("free: slot not found");
    return (-1);
}