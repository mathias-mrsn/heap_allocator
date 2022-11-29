/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_internal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:21:01 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/29 18:37:07 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "bucket.h"
#include "slot.h"
#include "thread_safety.h"

PRIVATE
void
_print_bucket (
    const bucket *bucket )
{
    switch(bucket->zone) {
        case TINY:
            PUTSTR("TINY :");
            break;
        case SMALL:
            PUTSTR("SMALL : ");
            break;
        case LARGE:
            PUTSTR("LARGE : ");
            break;
    }
    PUTADDR((void*)bucket)
    PUTSTR("\nPTR: ");
    PUTADDR(bucket->ptr);
    PUTSTR("\n");
    for (slot *slot = bucket->ptr; slot != NULL && slot->next; slot = slot->next) {
        PUTADDR((void*)slot + SIZEOF_SLOT);
        PUTSTR(" - ");
        PUTADDR((void *)slot->next);
        PUTSTR(" | size : ");
        PUTNBR((size_type)slot->next - ((size_type)slot + SIZEOF_SLOT))
        PUTSTR(" | state : ");
        if (slot->state == USED) {
            PUTSTR("USED");
        } else {
            PUTSTR("FREE");
        }
        PUTSTR("\n");
    }
}

void
show_alloc_mem_internal (void)
{
    THREAD_SAFETY(lock);
    
    for (int i = 0; i < 3; i++) {
        for (bucket *bucket = memory[i]; bucket != NULL; bucket = bucket->next) {
            _print_bucket(bucket);
        }
    }

    THREAD_SAFETY(unlock);
}