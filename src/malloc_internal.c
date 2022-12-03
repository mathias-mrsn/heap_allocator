/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:26:09 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 17:13:07 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_safety.h"
#include "pthread.h"
#include "unistd.h"
#include "commun.h"
#include "bucket.h"
#include "slot.h"
#include "meta.h"
#include <sys/mman.h>

pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;

PRIVATE
void *
_search_space (
    const size_type size,
    metadata m )
{
    const zone_type zone = TYPE_MATCHING(size);
    void *        ret;

    for (bucket *bucket = memory[zone]; bucket != NULL; bucket = bucket->next) {
        slot *slot;
        if ((slot = search_free_slot(bucket, size)) != NULL) {
            MALLOC_DEBUG("malloc: slot added in a old slot")
            ret = insert_slot(bucket, slot, size, m);
            return (ret);
        }
        if (free_space_left(bucket) >= size) {
            MALLOC_DEBUG("malloc: slot added at the end of the bucket")
            ret = new_slot(bucket, size, m);
            return (ret);
        }
    }
    return (NULL);
}

INLINE
void *
malloc_internal (
    size_t size,
    const char *func,
    const char *file,
    const size_t line )
{
    THREAD_SAFETY(lock);
    
    metadata m = {func, file, line};
    void * ret = NULL;
    
    if (size <= SMALL_SIZE && (ret = _search_space(size, m)) != NULL) {
        MALLOC_DEBUG("malloc: found space in bucket");
        THREAD_SAFETY(unlock);
        return (ret);
    } else {
        zone_type zone = TYPE_MATCHING(size);
        bucket * b = new_bucket(zone, size);

        if (b == NULL || b == MAP_FAILED) {
            MALLOC_DEBUG("malloc: new_bucket failed");
            THREAD_SAFETY(unlock);
            return (NULL);
        }
        push_back(b);
        ret = new_slot(b, size, m);
    }
    
    THREAD_SAFETY(unlock);
    
    return (ret);  
}
