/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/19 19:04:16 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_block.h"
#include "commun.h"
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// PRIVATE
mem_block *
create_block (
    const size_t zone_size,
    mem_block * prev,
    mem_block * next)
{

    // int fd = open ("/dev/zero", );
    // void * ptr = (void *)mmap(NULL, zone_size + BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0 );
    // close(fd);
    void * ptr = NULL;
    mem_block * block = (mem_block *)ptr;
    
    PUTADDR(ptr)

    if (block == MAP_FAILED || block == NULL) {
        LOG_ERROR("error: mmap() failed")
        return (MAP_FAILED);
    }
    
    ft_memset(block, 0, zone_size + BLOCK_SIZE);
    block->ptr = block + BLOCK_SIZE ;
    block->state = EMPTY;
    block->size = zone_size;
    block->prev = prev;
    block->next = next;
    
    return (block);
}

//!\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
