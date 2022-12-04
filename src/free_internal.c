/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 11:57:04 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include "slot.h"
#include "thread_safety.h"
#include "free_internal.h"

INLINE
void
free_internal (
    void * ptr,
    const char * func,
    const char * file,
    const size_t line )
{
    THREAD_SAFETY(lock);

    metadata m = {func, file, line};
    bucket * b = find(ptr);
    
    if (!b) {
        _FREE_ERR_IP(NULL)
        THREAD_SAFETY(unlock);
        return ;
    }
    if (b->zone == LARGE) {
        if ((void *)b->last + SIZEOF_SLOT != ptr) {
            _FREE_ERR_MS((void *)b->last + SIZEOF_SLOT)
        }
        unlink_bucket(b);
        destroy_bucket(b);
    } else {
        slot * s = find_slot(b, ptr);
        if (!s) {
            _FREE_ERR_IP(ptr)
        } else {
            if (s->state & FREED) {
                _FREE_ERR_DF(ptr)
            } else if (s->state & USED) {
                s->state = FREED;
                s->meta = m;
                if (ptr != (void *)s + SIZEOF_SLOT) {
                    _FREE_ERR_MS((void *)s + SIZEOF_SLOT)
                }
            } else {
                _FREE_ERR_IP(ptr)
            }
        }
    }
    
    THREAD_SAFETY(unlock);
}
