/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:21 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/27 20:16:06 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "slot.h"
#include "bucket.h"

#include <stdio.h>

void *
new_slot(
    bucket  *bucket,
    const size_t  size)
{
    slot *slot = bucket->last;
    
    // printf("%p\n", slot);
    slot->next = (void *)slot + size + SIZEOF_SLOT;
    // printf("%p\n", slot->next);
    // slot->next->next = NULL; 
    slot->state = USED;
    
    // printf("%zu\n", slot->next - bucket->last);
    bucket->last = slot->next; 
    // printf("%p\n", bucket->last);

    return ((void *)slot + SIZEOF_SLOT);
}

//! TODO: I have to test this function, I wrote it in 5 minutes.

void *
insert_slot (
    bucket* b,
    slot*   s,
    const size_t  size)
{
    const size_type size_free = (void*)s->next - ((void*)s + SIZEOF_SLOT);
    const size_type type = GET_TYPE(b->zone, size);
    slot*           save;

    if (size_free - size > type + SIZEOF_SLOT) {
        save = s->next;
        s->next = (void *)s + size + SIZEOF_SLOT;
        s->next->state = FREE;
        s->next->next = save;
        s->state = USED;
    } else {
        s->state = USED;
    }
    
    return ((void *)s + SIZEOF_SLOT);
}

inline
size_type
compute_slot_size (
    slot*   s )
{
    return ((void*)s->next - ((void *)s + SIZEOF_SLOT));
}