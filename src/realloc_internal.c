/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_internal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:14:49 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 12:49:09 by mamaurai         ###   ########.fr       */
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
    size_type len,
    const char * func,
    const char * file,
    const size_t line )
{
    void * ptr = NULL;
    metadata m = {func, file, line};
    
    if (b->size_allocated / LARGE_REALLOC_CONDITION < len) {
        MALLOC_DEBUG("realloc(): large case - pointer not reallocated\n");
        return (b->ptr);
    }
    if ((ptr = malloc_internal(len, func, file, line)) == NULL) {
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
    size_type len,
    const char * func,
    const char * file,
    const size_t line)
{
    slot * s = find_slot(b, ptr);
    metadata m = {func, file, line};
    
    if (!s) {
        _REALLOC_ERR_IP((void *)s + SIZEOF_SLOT)
        return (NULL);
    } else if (s->state == FREED) {
       _REALLOC_ERR_DF((void *)s + SIZEOF_SLOT);
        return (NULL);
    }
    
    void * new_ptr = NULL;
    const void * next_ptr = find_enough_space(b, s, len);
    const size_type expandable_size = next_ptr - ((void *)s + SIZEOF_SLOT);
    PUTNBR(expandable_size);
    
    if (expandable_size >= len) {
        MALLOC_DEBUG("realloc(): other cases - pointer not reallocated\n");
        s->next = (slot *)next_ptr;
        new_ptr = insert_slot(b, s, len, m);
    } else {
        if ((new_ptr = malloc_internal(len, func, file, line)) == NULL) {
            return (NULL);
        }
        MALLOC_DEBUG("realloc(): other cases - pointer reallocated\n");
        ft_memcpy(new_ptr, ptr, compute_slot_size(s));
        free_internal(ptr, func, file, line);
    }
    return (new_ptr);
}

void *
realloc_internal (
    void * ptr,
    const size_t len,
    const char * func,
    const char * file,
    const size_t line )
{
    bucket * b = find(ptr);
    void * new_ptr = NULL;
    
    if (!b) {
        WARNING("realloc(): invalid pointer");
        return (NULL);
    }
    if (b->zone == LARGE) {
        new_ptr = _large_case(b, len, func, file, line);
    } else {
        new_ptr = _other_cases(b, ptr, len, func, file, line);
    }
    return (new_ptr);
}