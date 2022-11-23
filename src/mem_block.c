/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/23 17:30:35 by mamaurai         ###   ########.fr       */
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
    block->zone_type = ZONE_TYPE_MATCHING(size_required);
    block->ptr = block + BLOCK_SIZE ;
    block->slots[0] = size_required;
        
    return (block);
}


/* TODO : rename push_back */
int
push_back (
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

PRIVATE
int
_insert_slot (
    mem_block *     block,
    const int       slot_idx,
    const size_t    size_required)
{
    const int previous_slot = block->slots[slot_idx - 1];
    const int value_to_insert = previous_slot + size_required;

    if (IS_FULL(block))
        return (SYSCALL_ERR);    
    for (int idx = slot_idx; idx < SLOT_BY_BLOCK; idx++) {
        block->slots[idx + 1] = block->slots[idx];
    }
    block->slots[slot_idx] = block->slots[slot_idx - 1] + size_required;
    
    return (1);
}

void *
reserve (
    mem_block * block, 
    const int obj,
    const size_t size_required)
{
    const int8_t slot_free = obj >> 16;
    const int8_t size_free = obj;
    void * ptr = NULL;

    if (block->slots[slot_free] == 0) {
        block->slots[slot_free] = size_required + block->slots[slot_free - 1];
        ptr = block->ptr + block->slots[slot_free - 1];
    }  else {
        if (size_free == size_required) {
            block->slots[slot_free] *= -1;
        } else {
            _insert_slot(block, slot_free, size_required);
        }
    }
    return ptr;
}

int
compute_free_space (
    mem_block * block,
    const size_t size_required )
{
    size_t size_free = 0;
    
    for (uint8_t i = 0; i < SLOT_BY_BLOCK; i++) {
        if (block->slots[i] < 0) {
            size_free = (block->slots[i] * -1) - ((i != 0) ? block->slots[i - 1] : 0);
        } else if (block->slots[i] == 0) {
            size_free = ZONE_TYPE_2_SIZE(block->zone_type) - block->slots[i - 1];
        }
        if (size_free >= size_required) {
            return ((i << 16) + size_free);
        }
    }
    return (SYSCALL_ERR);
}


/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/