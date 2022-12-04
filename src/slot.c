/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:21 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 13:11:57 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "slot.h"
#include "bucket.h"
#include "free_internal.h"
#include "meta.h"

NONNULL
void *
new_slot(
    bucket  *bucket,
    const size_t  size,
    metadata m)
{
    slot *slot = bucket->last;

    slot->next = (void *)slot + size + SIZEOF_SLOT;
    slot->next->state = EOB;
    slot->state = USED;    
    bucket->last = slot->next;
    slot->meta = m;
    
    return ((void *)slot + SIZEOF_SLOT);
}

NONNULL
void *
insert_slot (
    bucket* b,
    slot*   s,
    const size_t  size,
    metadata m)
{
    const size_type size_free = compute_slot_size(s);
    const size_type type = GET_TYPE_BELOW(b->zone);
    slot*           save;

    if (size_free - size > type + SIZEOF_SLOT) {
        save = s->next;
        s->next = (void *)s + size + SIZEOF_SLOT;
        s->next->state = FREED;
        s->next->next = save;
        MALLOC_DEBUG("malloc: insert_slot(): split slot");
    } else {
        MALLOC_DEBUG("malloc: insert_slot(): use old slot");
    }
    s->meta = m;
    s->state = USED;
    
    return ((void *)s + SIZEOF_SLOT);
}

INLINE
NONNULL
size_type
compute_slot_size (
    const slot * s )
{
    return ((void*)s->next - ((void *)s + SIZEOF_SLOT));
}

NONNULL
slot *
find_slot (
    const bucket * b,
    void * ptr )
{
    FOREACH_SLOT (b, s) {
        if ((ptr >= (void *)s && ptr < (void *)s->next)) {
            return (s);
        }
    }
    return (NULL);
}

NONNULL
size_type
compute_expandable_size (
    const bucket * b,
    const slot * s )
{
    size_type size = 0;
    slot *save = s->next;

    while (save && save->state & (FREED)) {
        size += compute_slot_size(save);
        save = save->next;
    }
    if (save && save->state & (EOB)) {
        size += free_space_left(b);
    }
    return (size);
}

NONNULL
void *
find_enough_space (
    const bucket * b,
    const slot * s,
    const size_type len )
{

    slot *save = s->next;

    while (save && save->state & (FREED)) {
        if (((void *)save->next - (((void *)s) + SIZEOF_SLOT)) >= len) {
            break;
        }
        save = save->next;
    }
    if (save && save->state & (EOB)) {
        return ((void *)b + (GET_SIZE(b->zone, b->size_allocated) + SIZEOF_BUCKET));
    }
    return ((void *)save->next);
}