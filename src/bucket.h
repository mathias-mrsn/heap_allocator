/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:20:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/27 20:03:10 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "commun.h"
#include "stddef.h"
#include "stdbool.h"
#include "stdint.h"
#include "slot.h"

typedef uint8_t zone_type;
typedef size_t  size_type;

/**
 * @brief Structure used to store a memory block.
 * 
 * @param ptr pointer to the first address of the memory block
 * @param zone type of zone (TINY, SMALL, LARGE)
 * @union {
 *      @param last pointer to the last slot of the block
 *      @param size_allocated size allocated only if the zone is LARGE
 * }
 * @param next pointer to the next block
 * @param prev pointer to the previous block
 * 
 * @struct total size -> 89
 */
typedef struct  s_bucket
{
    void    *   ptr;
    zone_type   zone : 2;
    union {
        slot *      last;
        size_t      size_allocated;
    };
    struct s_bucket * next;
    struct s_bucket * prev;
} PACKED        bucket;
#define SIZEOF_BUCKET sizeof(struct s_bucket)

/**
 * @brief Allocate a new bucket.
 * 
 * @return bucket* 
 */
bucket *
new_bucket (zone_type, size_type);

/**
 * @brief Push a bucket at the end of the memory list.
 * 
 * @param bucket bucket to push
 */
void
push_back (bucket *);

/**
 * @brief Return the amount of free space left at the end of the block.
 * 
 * @param bucket pointer to the block
 * @return size_type 
 */
size_type
free_space_left (bucket *);

//! #define END_OF_BUCKET() (bucket->ptr + ZONE_TYPE_2_SIZE(bucket->zone_type) - SIZEOF_SLOT)

/**
 * @brief Minimun of slot a zone must have.
 */
#define MIN_SLOT    100

/**
 * @brief Enum used to simplify the memory array reading.
 */
enum mem_access {
    BEGIN,
    END
};  

/**
 * @brief Enum used to simplify the zone type reading.
 */
enum type_size {
    TINY_SIZE = 256,
    MEDIUM_SIZE = 1024,
    LARGE_SIZE = -1
};

enum zone_size {
    TINY_ZONE = MIN_SLOT * (TINY_SIZE + SIZEOF_SLOT),
    MEDIUM_ZONE = MIN_SLOT * (MEDIUM_SIZE + SIZEOF_SLOT),
    LARGE_ZONE = -1
};

enum type {
    TINY,
    MEDIUM,
    LARGE
};

#define GET_SIZE(type, size) (type == TINY ? TINY_ZONE : (type == MEDIUM ? MEDIUM_ZONE : size))
#define GET_TYPE(type, size) (type == TINY ? TINY_SIZE : (type == MEDIUM ? MEDIUM_SIZE : size))

extern bucket * memory[3][2];

//// enum zone_size {
////     TINY_ZONE = SLOT_BY_BLOCK * MINIMUM_SIZE_REQUIRED,
////     MEDIUM_ZONE = SLOT_BY_BLOCK * TINY_ZONE
//// };

//// # define ZONE_SIZE_MATCHING(x) (x <= TINY_ZONE ? TINY_ZONE : (x <= MEDIUM_ZONE ? MEDIUM_ZONE : x))
//// # define ZONE_TYPE_MATCHING(x) (x <= TINY_ZONE ? TINY : (x <= MEDIUM_ZONE ? MEDIUM : LARGE))
//// # define ZONE_TYPE_2_SIZE(x) (x == TINY ? TINY_ZONE : (x == MEDIUM ? MEDIUM_ZONE : 0))
//// # define IS_LARGE(x) (x > MEDIUM_ZONE)

////# define IS_FULL(x) (x->slots[SLOT_BY_BLOCK - 1] != 0)

//// int
//// push_back (mem_block *);

//// mem_block *
//// create_block(const size_t);

//// int
//// compute_free_space (mem_block *, const size_t);

//// void *
//// reserve (mem_block *, const int, const size_t);


/*

PTR|SLOT->next = 0x20 = end of slot / SLOT at 0x20 with next = 0,70                                  SLOT_END -> prev = end_of bucket
[.....................................................................................................B--]

*/
