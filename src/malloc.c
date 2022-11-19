/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:26:09 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/19 19:07:01 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mem_block.h"
#include "sys/mman.h"
#include <stdio.h>

pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;

void *
malloc (size_t size)
{
    THREAD_SAFETY_PRIORITY(lock);

    mem_block * b = (mem_block *)create_block(1000, NULL, NULL);
    // if (b == MAP_FAILED) {
    //     THREAD_SAFETY_PRIORITY(unlock);        
    //     return (NULL);
    // }


    THREAD_SAFETY_PRIORITY(unlock);
    return (NULL);  
}