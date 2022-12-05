/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 13:42:18 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include "slot.h"

#include <sys/mman.h>
#include <assert.h>

bucket *        memory[3] = {0};

bucket *
new_bucket (
    const zone_type zone,
    const size_type size)
{
    const size_t    size_to_allocated = GET_SIZE(zone, size) + SIZEOF_BUCKET + SIZEOF_SLOT;
    bucket *bucket = mmap(NULL, size_to_allocated, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (bucket == MAP_FAILED) {
        MALLOC_DEBUG("malloc: mmap() failed");
        return (NULL);
    }
    ft_memset(bucket, 0, size_to_allocated);
    bucket->ptr = (void *)bucket + SIZEOF_BUCKET;
    bucket->zone = zone;
    bucket->last = (void *)bucket->ptr;
    bucket->last->state = EOB;
    bucket->size_allocated = size_to_allocated;
    return (bucket);
}

NONNULL
INLINE
void
unlink_bucket (
    bucket * b )
{
    const zone_type zone = b->zone;
    
    if (memory[zone] == b) {
        memory[zone] = b->next;
    }
    if (b->next) {
        b->next->prev = b->prev;
    }
    if (b->prev) {
        b->prev->next = b->next;
    }
}

NONNULL
void
destroy_bucket (
    bucket *bucket )
{
    if (munmap(bucket, bucket->size_allocated)) {
        MALLOC_DEBUG("malloc: munmap() failed\n")
        return;
    }
}

INLINE
NONNULL
void
push_back (
    bucket *bucket )
{
    const zone_type zone = bucket->zone;
    
    if (memory[zone] == NULL) {
        memory[zone] = bucket;
    } else {
        bucket->next = memory[zone];
        memory[zone]->prev = bucket;
        memory[zone] = bucket;
    }
}

INLINE
NONNULL
size_type
free_space_left (
    const bucket *bucket )
{
    slot *slot = bucket->last;
    const size_type size_total = GET_SIZE(bucket->zone, bucket->size_allocated);

    return (size_total - (((size_type)slot + SIZEOF_SLOT) - (size_type)bucket->ptr));
}

NONNULL
slot *
search_free_slot (
    const bucket *  bucket,
    const size_type size )
{
    FOREACH_SLOT (bucket, slot) {
        if (slot->state & FREED && compute_slot_size(slot) >= size) {
            return (slot);
        }
    }
    return (NULL);
}

NONNULL
bucket *
find (
    const void *ptr )
{
    for (zone_type i = 0; i < 3; i++) {
        for (bucket *bucket = memory[i]; bucket != NULL; bucket = bucket->next) {
            if (ptr >= bucket->ptr && ptr < (void *)bucket->ptr + GET_SIZE(bucket->zone, bucket->size_allocated)) {
                return (bucket);
            }
        }
    }
    return (NULL);
}

void
merge_freed_slots (
    bucket * bucket)
{    
    FOREACH_SLOT (bucket, slot) {
        if ((slot->state & FREED) && (slot->next->state & (FREED | EOB))) {
            if (slot->next->state & EOB) {
                slot->state = EOB;
                slot->next = NULL;
                bucket->last = slot;
            } else {
                slot->next = slot->next->next;
            }
            slot = bucket->ptr;        
        }        
    }
}

size_type
compute_space_left (
    const bucket * bucket )
{
    size_type space_left = 0;
    
    FOREACH_SLOT (bucket, slot) {
        if (slot->state & FREED) {
            space_left += compute_slot_size(slot);
        }
    }
    return (space_left);
}

int
is_freed (
    const bucket * bucket )
{
    FOREACH_SLOT (bucket, slot) {
        if (!(slot->state & FREED)) {
            return (false);
        }
    }
    return (true);
}


/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/
