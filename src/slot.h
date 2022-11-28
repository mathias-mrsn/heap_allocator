/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:03 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/28 17:28:19 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdbool.h"

struct s_bucket;
typedef struct s_bucket bucket;
typedef size_t size_type;

/**
 * @brief Structure used to store every slot location
 * 
 * @param is_free 1 if the slot is free, 0 if used or 2 if the slot is the last one.
 * @param next pointer to the next slot.
 * 
 * @struct total size -> 9 bytes
 */
typedef struct  s_slot {
    bool    state; // FREE, USED // ? END_OF_BLOCK
    struct s_slot * next;
} PACKED        slot;
#define SIZEOF_SLOT sizeof(struct s_slot)

enum state {
    FREE,
    USED
};

/**
 * @brief Create a new slot at the end of the bucket.
 * 
 * @param bucket The bucket to which the slot belongs
 * @param size The amount of memory asked.
 * @return void* Return the address of the slot ptr 
 */
void *
new_slot(
    bucket *bucket,
    const size_t size);

//     void
// nb_slot (
//     bucket *bucket );

/**
 * @brief Insert a slot inside the bucket. Only if a usuned slot is found.
 * 
 * @param b Bucket to which the slot belongs
 * @param s Location of the free slot
 * @param size Size of the memory asked
 * @return void* Pointer to the slot ptr
 */
void *
insert_slot (
    bucket* b,
    slot*   s,
    const size_t  size);

/**
 * @brief Return the size of the slot
 * 
 * @param s Current slot to compute
 * @return size_type Size of the slot
 */
size_type
compute_slot_size (
    const slot * s );

/**
 * @brief Free a slot that contains the ptr
 * 
 * @param b Bucket to which the slot belongs
 * @param ptr Pointer to search
 * 
 * @return 0 if the slot has been freed, 1 if the ptr isn't the begin of the slot or -1 if the ptr hasn't been found.
 */
int
free_slot (
    bucket * b,
    const void * ptr );