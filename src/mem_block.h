/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:20:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/22 19:40:35 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"
#include "stdint.h"

/* ATTRIBUTES */

#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))

/**
 * @brief The number of mallocs that can be stored in a block.
 */
#define SLOT_BY_BLOCK 32

/**
 * @brief The minimum size for allocate memory in block.
 * 
 * @example If I request 2 bytes and the MSR is 32, the block will allocate 32 bytes. 
 */
#define MINIMUM_SIZE_REQUIRED 16
#define MIN_SIZE(x) (x < MINIMUM_SIZE_REQUIRED ? MINIMUM_SIZE_REQUIRED : x)

/**
 * @brief Structure used to store a memory block.
 * 
 * @param ptr pointer to the first address of the memory block
 * @param zone_type type of zone (TINY, SMALL, LARGE)
 * @union {
 *      @param slots array used to store every pointer address
 *      @param size_allocated size allocated only if the zone_type is LARGE
 * }
 * @param next pointer to the next block
 * @param prev pointer to the previous block
 * 
 * @struct total size -> 89
 */
typedef struct  s_mem_block
{
    void    *ptr;
    uint8_t zone_type;
    union {
        int16_t     slots[SLOT_BY_BLOCK];
        uint32_t    size_allocated;
    };
    struct s_mem_block * next;
    struct s_mem_block * prev;
} PACKED        mem_block;

/**
 * @brief Enum used to simplify the memory array reading.
 */
enum mem_access {
    MEM_BEGIN,
    MEM_END
};

/**
 * @brief Enum used to simplify the zone type reading.
 */
enum zone_type {
    TINY,
    MEDIUM,
    LARGE
};

enum zone_size {
    TINY_ZONE = SLOT_BY_BLOCK * MINIMUM_SIZE_REQUIRED,
    MEDIUM_ZONE = SLOT_BY_BLOCK * TINY_ZONE
};

# define ZONE_SIZE_MATCHING(x) (x <= TINY_ZONE ? TINY_ZONE : (x <= MEDIUM_ZONE ? MEDIUM_ZONE : x))
# define ZONE_TYPE_MATCHING(x) (x <= TINY_ZONE ? TINY : (x <= MEDIUM_ZONE ? MEDIUM : LARGE))
# define ZONE_TYPE_2_SIZE(x) (x == TINY ? TINY_ZONE : (x == MEDIUM ? MEDIUM_ZONE : 0))
# define BLOCK_SIZE sizeof(mem_block)
# define IS_LARGE(x) (x > MEDIUM_ZONE)

int
add_block_back (mem_block *);

mem_block *
create_block(const size_t);

int*
compute_free_space (mem_block *, const size_t);

void *
reserve (mem_block *, const uint8_t, const size_t);


/*
 [ ] Remove block from the list
 [ ] Find block with ...
 [ ] Create fonction to remove old negative slot
*/
