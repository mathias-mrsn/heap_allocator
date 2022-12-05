/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:20:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 13:38:26 by mamaurai         ###   ########.fr       */
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
 * @param last pointer to the last slot of the block
 * @param size_allocated size allocated
 * @param next pointer to the next block
 * @param prev pointer to the previous block
 * 
 * @struct total size -> 89
 */
typedef struct  s_bucket
{
    void    *   ptr;
    zone_type   zone : 2;
    slot *      last;
    size_t      size_allocated;
    struct s_bucket * next;
    struct s_bucket * prev;
} PACKED        bucket;
#define SIZEOF_BUCKET sizeof(struct s_bucket)

/**
 * @brief Allocate a new bucket.
 */
bucket *
new_bucket (
    zone_type,
    size_type );

/**
 * @brief Unlink the bucket from the linked list
 */
void
unlink_bucket (
    bucket * b );

/**
 * @brief Munmap the current bucket.
 */
void
destroy_bucket (
    bucket *bucket );

/**
 * @brief Push a bucket at the end of the memory list.
 */
void
push_back (
    bucket * );

/**
 * @brief Return the amount of free space left at the end of the block.
 */
size_type
free_space_left (
    const bucket * );

/**
 * @brief Return a slot if this slot has enough space.
 */
slot *
search_free_slot (
    const bucket *  bucket,
    const size_type size );

/**
 * @brief Search a bucket by its pointer.
 */
bucket *
find (
    const void *ptr );

/**
 * @brief Merge every free space between each slots.
 */
void
merge_freed_slots (
    bucket * bucket);

/**
 * @brief Check if the bucket is empty.
*/
int
is_freed (
    const bucket * b );

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
    SMALL_SIZE = 2048,
    LARGE_SIZE = -1
};

enum zone_size {
    TINY_ZONE = MIN_SLOT * (TINY_SIZE + SIZEOF_SLOT),
    SMALL_ZONE = MIN_SLOT * (SMALL_SIZE + SIZEOF_SLOT),
    LARGE_ZONE = -1
};

enum type {
    TINY,
    SMALL,
    LARGE
};

#define GET_SIZE(type, size) (type == TINY ? TINY_ZONE : (type == SMALL ? SMALL_ZONE : size + SIZEOF_SLOT))
#define GET_TYPE(type, size) (type == TINY ? TINY_SIZE : (type == SMALL ? SMALL_SIZE : size))
#define GET_TYPE_BELOW(type) (type == TINY ? 0 : (type == SMALL ? TINY_SIZE : SMALL_SIZE))
#define TYPE_MATCHING(size)  (size <= TINY_SIZE ? TINY : (size <= SMALL_SIZE ? SMALL : LARGE))

extern bucket * memory[3];
