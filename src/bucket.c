/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 00:54:00 by mamaurai         ###   ########.fr       */
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
    const size_t    size_to_allocated = GET_SIZE(zone, size) + SIZEOF_BUCKET;
    bucket *bucket = mmap(NULL, size_to_allocated, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    if (bucket == MAP_FAILED) {
        MALLOC_DEBUG("malloc: mmap() failed");
        return (NULL);
    }
    ft_memset(bucket, 0, size_to_allocated);
    bucket->ptr = (void *)bucket + SIZEOF_BUCKET;
    bucket->zone = zone;
    if (zone == LARGE) {
        bucket->size_allocated = size;
    } else {
        bucket->last = (void *)bucket->ptr;
        bucket->last->state = EOB;
    }
    return (bucket);
}

void
destroy_bucket (
    bucket *bucket )
{
    const size_type size = GET_SIZE(bucket->zone, bucket->size_allocated) + SIZEOF_BUCKET;
    if (munmap(bucket, size)) {
        MALLOC_DEBUG("malloc: munmap() failed\n")
        return;
    }
}

INLINE
void
push_back (
    bucket *bucket )
{
    const zone_type zone = bucket->zone;
    
    if (memory[zone] == NULL) {
        memory[zone] = bucket;
    } else {
        bucket->next = memory[zone];
        memory[zone] = bucket;
    }
}

INLINE
size_type
free_space_left (
    const bucket *bucket )
{
    slot *slot = bucket->last;
    const size_type size_total = GET_SIZE(bucket->zone, bucket->size_allocated);

    return (size_total - (((size_type)slot + SIZEOF_SLOT) - (size_type)bucket->ptr));
}

slot *
search_free_slot (
    const bucket *  bucket,
    const size_type size )
{
    FOREACH_SLOT (bucket, slot) {
        if (slot->state & FREE && compute_slot_size(slot) >= size) {
            return (slot);
        }
    }
    return (NULL);
}

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

//* I have to find a smart way to degragment the bucket
int
glue_slots (
    const bucket * bucket)
{
    return (1);
}

size_type
merge_freed_slots (
    const bucket * bucket)
{
    size_t count = 0;
    
    FOREACH_SLOT (bucket, slot) {
        if ((slot->state & (FREED | FREE)) && (slot->next->state & (FREED | FREE))) {
            if (slot->next->state & FREE) {
                slot->state = FREE;
            }
            slot->next = slot->next->next;
            count++;
        }
    }

    return (count);
}

size_type
compute_space_left (
    const bucket * bucket )
{
    size_type space_left = 0;
    
    FOREACH_SLOT (bucket, slot) {
        if (slot->state & (FREE | FREED)) {
            space_left += compute_slot_size(slot);
        }
    }
    return (space_left);
}


/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/
