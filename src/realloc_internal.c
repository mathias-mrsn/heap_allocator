/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_internal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:14:49 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 13:38:58 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "malloc_internal.h"
#include "free_internal.h"
#include "realloc_internal.h"

PRIVATE
void *
_large_case (
    bucket * b,
    size_type len )
{
    void * ptr = NULL;
    
    if (b->size_allocated / LARGE_REALLOC_CONDITION < len) {
        MALLOC_DEBUG("realloc(): large case - pointer not reallocated\n");
        return (b->ptr);
    }
    if ((ptr = malloc_internal(len)) == NULL) {
        return (NULL);
    }
    ft_memcpy(ptr, b->ptr, b->size_allocated);
    unlink_bucket(b);
    destroy_bucket(b);
    MALLOC_DEBUG("realloc(): large case - pointer reallocated\n");
    return (ptr);
}

PRIVATE
void *
_other_cases (
    bucket * b,
    void * ptr,
    size_type len)
{
    slot * s = find_slot(b, ptr);
    
    if (!s) {
        WARNING("realloc(): invalid pointer\n");
        return (NULL);
    } else if (s->state == FREED) {
        WARNING("realloc(): pointer already freed\n");
        return (NULL);
    }
    
    void * new_ptr = NULL;
    const void * next_ptr = find_next_slot_used(b, s);
    const size_type expandable_size = next_ptr - ((void *)s + SIZEOF_SLOT);
    
    if (expandable_size >= len) {
        MALLOC_DEBUG("realloc(): other cases - pointer not reallocated\n");
        s->next = (slot *)next_ptr;
        new_ptr = insert_slot(b, s, len);
    } else {
        if ((new_ptr = malloc_internal(len)) == NULL) {
            return (NULL);
        }
        MALLOC_DEBUG("realloc(): other cases - pointer reallocated\n");
        ft_memcpy(new_ptr, ptr, compute_slot_size(s));
        free_internal(ptr);
    }
    return (new_ptr);
}

void *
realloc_internal (
    void * ptr,
    const size_t len )
{
    bucket * b = find(ptr);
    void * new_ptr = NULL;
    
    if (!b) {
        WARNING("realloc(): invalid pointer");
        return (NULL);
    }
    if (b->zone == LARGE) {
        new_ptr = _large_case(b, len);
    } else {
        new_ptr = _other_cases(b, ptr, len);
    }
    return (new_ptr);
}