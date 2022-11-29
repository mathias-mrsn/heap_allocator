/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/29 18:13:13 by mamaurai         ###   ########.fr       */
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

    assert(bucket != MAP_FAILED);
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
    }
    return (bucket);
}

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
    for (slot *slot = bucket->ptr; slot != NULL && slot->next != NULL ; slot = slot->next) {
        if (slot->state == FREE && compute_slot_size(slot) >= size) {
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

/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/
