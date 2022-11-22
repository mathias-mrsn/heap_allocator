/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/22 19:39:24 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_block.h"
#include "commun.h"
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

mem_block *
create_block (
    const size_t size_required )
{
    const size_t zone_size = ZONE_SIZE_MATCHING(size_required);

    void * ptr = (void *)mmap(NULL, zone_size + BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
    mem_block * block = (mem_block *)ptr;
    
    if (block == MAP_FAILED || block == NULL) {
        LOG_ERROR("error: mmap() failed")
        return (MAP_FAILED);
    }
    
    ft_memset(block, 0, zone_size + BLOCK_SIZE);
    block->ptr = block + BLOCK_SIZE ;
    block->slots[0] = size_required;

    // print_mem_block(block);
    
    return (block);
}


/* TODO : rename push_back */
int
add_block_back (
    mem_block * block )
{
    const int8_t zone = block->zone_type;

    if (memory[zone][MEM_BEGIN] == NULL) {
        memory[zone][MEM_BEGIN] = block;
        memory[zone][MEM_END] = block;
    } else {
        memory[zone][MEM_END]->next = block;
        block->prev = memory[zone][MEM_END];
        memory[zone][MEM_END] = block;
    }
    return (1);
}

void *
reserve (
    mem_block * block, 
    const int8_t free_slot,
    const size_t size)
{
    if (free_slot == 0) {
        block->slots[free_slot] = size + block->slots[free_slot - 1];
        return (block->ptr);
    } else {
        
    }
}

int [2]
compute_free_space (
    mem_block * block,
    const size_t size_required )
{
    size_t size_free = 0;
    
    for (uint8_t i = 0; i < SLOT_BY_BLOCK; i++) {
        LOG("loop")
        if (block->slots[i] < 0) {
            size_free = (block->slots[i] * -1) - ((i != 0) ? block->slots[i - 1] : 0);
        } else if (block->slots[i] == 0) {
            size_free = ZONE_TYPE_2_SIZE(block->zone_type) - block->slots[i - 1];
        }
        if (size_free >= size_required) {
            return ((int[2]){i, size_free});
        }
    }
    return (SYSCALL_ERR);
}


/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/