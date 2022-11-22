/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:26:09 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/22 19:41:29 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "mem_block.h"
#include "sys/mman.h"
#include <stdio.h>
#include "commun.h"
#include <stdbool.h>

pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;
mem_block * memory[3][2] = {0};

PRIVATE
void *
_insert_free_space (
    size_t size )
{
    const char zone = ZONE_TYPE_MATCHING(size);
    int * free_slot = NULL;
    void * ptr = NULL;
    mem_block * block = memory[zone][MEM_BEGIN];

    while (block != NULL) {
        if ((free_slot = compute_free_space(block, size)) != SYSCALL_ERR) {
            PUTNBR(free_slot);
            ptr = reserve(block, free_slot, size);
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
malloc (size_t size)
{
    THREAD_SAFETY_PRIORITY(lock);
    
    size = MIN_SIZE(size);
    mem_block * block = NULL;
    void * ptr = NULL;
    
    if (!IS_LARGE(size) && (ptr = _insert_free_space(size)) != NULL) {
        return (ptr);
    }
    
    block = (mem_block *)create_block(size);
    if (block == MAP_FAILED)
        return (NULL);       
    if (add_block_back(block) == SYSCALL_ERR) {
        return (NULL);
    }

    // print_full_zone(TINY);
    THREAD_SAFETY_PRIORITY(unlock);
    return (block->ptr);  
}