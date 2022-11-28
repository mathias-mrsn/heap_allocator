/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:26:09 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/28 15:31:26 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_safety.h"
#include "pthread.h"
#include "unistd.h"
#include "commun.h"
#include "bucket.h"
#include "slot.h"
#include "print_memory.h"
#include <sys/mman.h>

pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;

void *
malloc (
    size_t size )
{
    THREAD_SAFETY(lock);
    
    void * ret = NULL;
    
    if ((ret = search_space(size)) != NULL) {
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
        ret = new_slot(b, size);
    }
        
    // print_memory();
    
    THREAD_SAFETY(unlock);
    
    return (ret);  
}
