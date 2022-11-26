/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:10:21 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/26 16:57:08 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "slot.h"
#include "bucket.h"

#include <stdio.h>

void
new_slot(
    bucket *bucket,
    size_t size)
{
    slot *slot = bucket->last;
    
    printf("%p\n", slot);
    slot->next = (void *)slot + size + SIZEOF_SLOT;
    printf("%p\n", slot->next);
    slot->next->next = NULL;
    slot->state = USED;
    
    printf("%zu\n", slot->next - bucket->last);
    bucket->last = slot->next; 
    printf("%p\n", bucket->last);
}
