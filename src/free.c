/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/28 18:22:56 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include "slot.h"
#include "thread_safety.h"
#include <assert.h>

PRIVATE
INLINE
void
_free_internal (
    void * ptr )
{
    bucket * b = find(ptr);
    if (b == NULL) {
        ERROR("free(): invalid pointer");
        assert(0);
        THREAD_SAFETY(unlock);
        return ;
    }
    const int ret = free_slot(b, ptr);
    switch (ret) {
        case -1:
            ERROR("free(): invalid pointer");
            assert(0);
            break;
        case 1:
            WARNING("free(): this pointer isn't at the begin of a slot; the entire slot has been freed");
            break;
        default:
            break;
    }   
}

void
free (
    void * ptr )
{
    THREAD_SAFETY(lock);
    _free_internal(ptr);
    THREAD_SAFETY(unlock);
}