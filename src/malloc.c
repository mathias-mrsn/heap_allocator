/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:26:09 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/27 19:40:21 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread_safety.h"
#include "pthread.h"
#include "unistd.h"
#include "commun.h"
#include "bucket.h"
#include "slot.h"
#include "print_memory.h"

pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;

void *
malloc (
    size_t size )
{
    THREAD_SAFETY(lock);

    bucket *bucket = new_bucket(TINY, size);
    
    PUTNBR(free_space_left(bucket));
    new_slot(bucket, 1000);
    new_slot(bucket, 1000);
    ft_print_memory((void*)bucket, TINY_ZONE);
    THREAD_SAFETY(unlock);
    return (NULL);  
}
