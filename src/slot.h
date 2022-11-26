/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:03 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/26 16:16:32 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdbool.h"

struct s_bucket;
typedef struct s_bucket bucket;

// **
//  * @brief Structure used to store every slot location
//  * 
//  * @param is_free 1 if the slot is free, 0 if used or 2 if the slot is the last one.
//  * @param next pointer to the next slot.
//  * 
//  * @struct total size -> 9 bytes
//  */
typedef struct  s_slot {
    bool    state; // FREE, USED // ? END_OF_BLOCK
    struct s_slot * next;
} PACKED        slot;
#define SIZEOF_SLOT sizeof(struct s_slot)

enum state {
    FREE,
    USED
};

void
new_slot(
    bucket *bucket,
    size_t size);
