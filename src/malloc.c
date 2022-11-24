/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:26:09 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/24 16:59:01 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mem_block.h"
#include "sys/mman.h"
#include <stdio.h>
#include "commun.h"
#include <stdbool.h>
#include "leaks.h"

#include <unistd.h>

pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;
mem_block * memory[3][2] = {0};

PRIVATE
void *
_insert_free_space (
    size_t size )
{
    const char zone = ZONE_TYPE_MATCHING(size);
    int  obj = 0;
    void * ptr = NULL;
    mem_block * block = memory[zone][MEM_BEGIN];

    while (block != NULL) {
        if ((obj = compute_free_space(block, size)) != SYSCALL_ERR) {
            ptr = reserve(block, obj, size);
            break;
        } else {
            block = block->next;
        }
    }
    return (ptr);
}

/*
    TODO : find way to return two value at the same time 
*/

void *
malloc (
    size_t size )
{
    if (pthread_mutex_lock(&malloc_lock)) {
        write(1, "salut\n", 6);
        return (NULL);
    }
    
    size = MIN_SIZE(size);
    mem_block * block = NULL;
    void * ptr = NULL;
    
    LOG_ERROR("new malloc")
    if (!IS_LARGE(size) && (ptr = _insert_free_space(size)) != NULL) {
        print_full_zone(TINY);
        print_full_zone(MEDIUM);
        THREAD_SAFETY_PRIORITY(unlock);
        return (ptr);
    }
    
    block = (mem_block *)create_block(size);
    LOG_ERROR("out of create_block")
    if (block == MAP_FAILED) {
        THREAD_SAFETY_PRIORITY(unlock)
        return (NULL);   
    }
    if (push_back(block) == SYSCALL_ERR) {
        THREAD_SAFETY_PRIORITY(unlock);
        return (NULL);
    }

    // print_full_zone(TINY);
    // print_full_zone(MEDIUM);
    THREAD_SAFETY_PRIORITY(unlock);
    return (block->ptr);  
}
