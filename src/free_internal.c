/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:39:05 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 23:12:51 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include "slot.h"
#include "thread_safety.h"
#include "free_internal.h"
#include "print_memory.h"

/*   PRINT HELPER   */

PRIVATE
INLINE
void
_err_iv (
    void * ptr,
    const metadata m )
{
    PUTERR("=================================================================\n")
    WARNING(BWHITE"free()"RESET": invalid pointer === cannot free a unknown address\n\n");
    if (ptr) {
        PUTERR("=== Memory freed ===\n\n")
        ft_print_memory(ptr, 128);
    } else {
        PUTERR("This address is not in the heap === ");
        PUTADDRR(ptr)
        PUTERR("\n");
    }
    PUTERR(BHCYAN"\nFunction called by >>> \n\t"YELLOWHB);
    PRINT_CALL_LOCATION(m);
    PUTERR(RESET"\n=================================================================\n")
}

PRIVATE
INLINE
void
_err_mos (
    void * ptr,
    const metadata m )
{
    PUTERR("=================================================================\n")
    WARNING(BWHITE"free()"RESET": this pointer isn't at the begin of a slot === the entire slot has been freed\n\n");
    PUTERR("=== Memory freed ===\n\n")
    ft_print_memory(ptr, 128);
    PUTERR(BHCYAN"\nFunction called by >>> \n\t"YELLOWHB);
    PRINT_CALL_LOCATION(m);
    PUTERR(RESET"\n=================================================================\n")
}

PRIVATE
INLINE
void
_err_df (
    void * ptr,
    const metadata m,
    const metadata m2 )
{
    PUTERR("=================================================================\n")
    WARNING(BWHITE"free()"RESET": double free === this address has already been freed\n\n");
    // ft_print_memory(ptr, 128);
    PUTERR(BHCYAN"Function called by >>> \n\t"YELLOWHB);
    PRINT_CALL_LOCATION(m);
    PUTERR(RESET BHCYAN"\n\nPreviously freed by >>> \n\t"YELLOWHB);
    PRINT_CALL_LOCATION(m2);
    PUTERR(RESET"\n=================================================================\n")
}

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
        _err_iv(NULL, m);
        THREAD_SAFETY(unlock);
        return ;
    }
    if (b->zone == LARGE) {
        if ((void *)b->last + SIZEOF_SLOT != ptr) {
            _err_mos((void *)b->last + SIZEOF_SLOT, m);
        }
        unlink_bucket(b);
        destroy_bucket(b);
    } else {
        slot * s = find_slot(b, ptr);
        if (!s) {
            _err_iv(ptr, m);
        } else {
            if (s->state & FREED) {
                _err_df(ptr, m, s->meta);
            } else if (s->state & USED) {
                s->state = FREED;
                s->meta = m;
                if (ptr != (void *)s + SIZEOF_SLOT) {
                    _err_mos(ptr, m);
                }
            } else {
                _err_iv(ptr, m);
            }
        }
    }
    THREAD_SAFETY(unlock);
}
