/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:16:25 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 18:42:28 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaks_internal.h"
#include "thread_safety.h"
#include "commun.h"
#include "bucket.h"
#include "slot.h"


/* PRINT HELPER */

PRIVATE
void
_print_slot (
    const slot * s )
{
    PUTERR("=== ")
    PUTNBRR(compute_slot_size(s))
    PUTERR(" bytes are possibly lost\n")
    PUTERR("=== \t at: "YELLOWHB)
    PUTERR(s->meta.func)
    PUTERR("(")
    PUTERR(s->meta.file)
    PUTERR(":")
    PUTNBRR(s->meta.line)
    PUTERR(")"RESET"\n===\n")
}


PRIVATE
void
_print_all (
    const size_type bucket_count,
    const size_type bytes_count )
{
    bucket * b;

    PUTERR("=================================================================\n")
    PUTERR("=== "BHPURPLE"leaks(): a memory leak detector\n"RESET"===\n")
    PUTERR("=== Heap summary: \n")
    PUTERR("=== \tin use at the exit: ")
    PUTNBRR(bytes_count)
    PUTERR(" bytes in ")
    PUTNBRR(bucket_count)
    PUTERR(" blocks\n===\n")

#if (CHECK_ALL == 1)

    for (int i = 0; i < 3; i++) {
        for (b = memory[i]; b; b = b->next) {
            FOREACH_SLOT(b, s) {
                if (s->state & USED)
                    _print_slot(s);
            }
        }
    }

#else
    PUTERR("=== to check all the heap, recompile with CHECK_ALL=1 in Makefile\n")
#endif

    PUTERR("=================================================================\n")
}

/* UTILS */

PRIVATE
void
_clean_empty_buckets (
    const zone_type zone )
{
    bucket *    b = memory[zone];
    
    while (b) {
        if (is_freed(b)) {
            unlink_bucket(b);
            destroy_bucket(b);
            b = memory[zone];
        } else {
            b = b->next;
        }
    }
}

PRIVATE
size_type
_count_blocks (
    bucket * b )
{
    size_type count = 0;
    
    for (; b; b = b->next, count++);
    return (count);
}

PRIVATE
size_type
_count_bytes (
    bucket * b )
{
    size_type count = 0;
    
    for (; b; b = b->next) {
        FOREACH_SLOT (b, s) {
            if (!(s->state & FREED)) {
                count += compute_slot_size(s);
            }
        }
    }
    return (count);
}

/* PUBLIC FUNCTIONS */

int
leaks_internal (void)
{
    THREAD_SAFETY(lock)
    
    size_type nb_blocks = 0;
    size_type nb_bytes = 0;
    
    for (int i = 0; i < 3; i++) {
        _clean_empty_buckets(i);
        nb_blocks += _count_blocks(memory[i]);
        nb_bytes += _count_bytes(memory[i]);
    }
    _print_all(nb_blocks, nb_bytes);

    THREAD_SAFETY(unlock)

    return (1);
}
