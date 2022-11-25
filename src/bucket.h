/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:20:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/25 16:01:18 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"
#include "stdint.h"


// **
//  * @brief Defines to simplify the use of the attributes. 
//  * 
//  */
#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))

// **
//  * @brief The minimum size for allocate memory in block.
//  * 
//  * @example If I request 2 bytes and the MSR is 32, the block will allocate 32 bytes. 
//  */
#define MINIMUM_SIZE_REQUIRED 16

// **
//  * @brief Structure used to store every slot location
//  * 
//  * @param is_free 1 if the slot is free, 0 if used or 2 if the slot is the last one.
//  * @param prev pointer to the previous slot
//  * 
//  * @struct total size -> 9 bytes
//  */
typedef struct  s_slot {
    bool    state; // FREE, USED, END_OF_BLOCK
    struct s_slot * prev; //! it can maybe be a uint32_t to save 4 bytes because we cannot put more than INTMAX alloc into a TINY/MEDIUM block
} PACKED        slot;
#define SIZEOF_SLOT sizeof(slot)

enum state {
    FREE,
    USED,
    END_OF_BLOCK  
};

// **
//  * @brief Structure used to store a memory block.
//  * 
//  * @param ptr pointer to the first address of the memory block
//  * @param zone type of zone (TINY, SMALL, LARGE)
//  * @union {
//  *      @param last pointer to the last slot of the block
//  *      @param size_allocated size allocated only if the zone is LARGE
//  * }
//  * @param next pointer to the next block
//  * @param prev pointer to the previous block
//  * 
//  * @struct total size -> 89
// */
typedef struct  s_bucket
{
    void    *ptr;
    uint8_t zone : 2;
    union {
        t_slot *    last;
        size_t      size_allocated;
    };
    struct s_bucket * next;
    struct s_bucket * prev;
} PACKED        bucket;
#define SIZEOF_BUCKET sizeof(slot)

typedef uint8_t zone_type;

//! #define END_OF_BUCKET() (bucket->ptr + ZONE_TYPE_2_SIZE(bucket->zone_type) - SIZEOF_SLOT)

// **
//  * @brief Minimun of slot a zone must have.
//  */
#define MIN_SLOT    100

// **
//  * @brief Enum used to simplify the memory array reading.
//  */
enum mem_access {
    MEM_BEGIN,
    MEM_END
};  

// **
//  * @brief Enum used to simplify the zone type reading.
//  */
enum zone_size {
    TINY = MIN_SLOT * TINY_SIZE,
    MEDIUM = MIN_SLOT * MEDIUM_SIZE,
    LARGE = -1
};

enum type_size {
    TINY_SIZE = 256,
    MEDIUM_SIZE = 1024,
    LARGE_SIZE = -1
}

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
