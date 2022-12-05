/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:03 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 13:51:22 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdbool.h"
#include "meta.h"

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
    char    state; // FREE, USED, FREED
#if (CHECK_ALL)
    metadata meta;
#endif
    struct s_slot * next;
} PACKED        slot;
#define SIZEOF_SLOT sizeof(struct s_slot)

enum state {
    FREED = 0x1,
    USED = 0x2,
    EOB = 0x4,
};

/**
 * @brief Create a new slot at the end of the bucket. 
 */
void *
new_slot(
    bucket *bucket,
    const size_t size,
    metadata m);

//     void
// nb_slot (
//     bucket *bucket );

/**
 * @brief Insert a slot inside the bucket. Only if a usuned slot is found.
 */
void *
insert_slot (
    bucket* b,
    slot*   s,
    const size_t  size,
    metadata m);

/**
 * @brief Return the size of the slot
 */
size_type
compute_slot_size (
    const slot * s );

/**
 * @brief Return the slot that contains the ptr
 */
slot *
find_slot (
    const bucket * b,
    void * ptr );

/**
 * @brief Return the amount of space that can be expanded
 */
size_type
compute_expandable_size (
    const bucket * b,
    const slot * s );

void *
find_enough_space (
    const bucket * b,
    const slot * s ,
    const size_type len);

#define FOREACH_SLOT(bucket_name, slot_name) \
    for (slot * slot_name = bucket_name->ptr; slot_name != NULL && slot_name->state != EOB ; slot_name = slot_name->next)