/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/26 16:48:27 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "slot.h"

bucket *        memory[3][2] = {0};

bucket *
new_bucket (
    const zone_type zone,
    const size_type size)
{
    const size_t    size_to_allocated = GET_SIZE(zone, size) + SIZEOF_BUCKET;
    bucket *bucket = mmap(NULL, size_to_allocated, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    assert(bucket != MAP_FAILED);
    if (bucket == MAP_FAILED) {
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
    
    if (memory[zone][END] == NULL) {
        memory[zone][END] = bucket;
        memory[zone][BEGIN] = bucket;
    } else {
        memory[zone][END]->next = bucket;
        bucket->prev = memory[zone][END];
        memory[zone][END] = bucket;
    }
}

size_type
free_space_left (
    bucket *bucket )
{
    slot *slot = bucket->last;
    const size_type size_total = GET_SIZE(bucket->zone, bucket->size_allocated);

    // for (; slot != NULL && slot->next != NULL; slot = slot->next);

    printf("%zu\n\n", ((size_type)slot + SIZEOF_SLOT) - (size_type)bucket->ptr);

    return (size_total - (((size_type)slot + SIZEOF_SLOT) - (size_type)bucket->ptr));
}

/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/
