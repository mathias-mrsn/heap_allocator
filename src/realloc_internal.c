/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_internal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:14:49 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 18:40:58 by mamaurai         ###   ########.fr       */
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
    size_type len)
{
    
}

// PRIVATE
// void *
// _recall_malloc (
//     const bucket * b,
//     size_t len )
// {
//     void * ptr = NULL;

//     if ((ptr = malloc_internal(len)) == NULL) {
//         return (NULL);
//     }
    
//     ft_memcpy(ptr, b->ptr, b->size_allocated);
//     free_internal(b->ptr);
//     return (ptr);
// }

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
        new_ptr = _other_cases(b, len);
    }

    
    //! NUL FAIS MIEUX
    // else {
    //     slot * s = find_slot(b, ptr);
        
        
    //     if (s->next->state & (FREE | FREED) && compute_expandable_size(b, s) >= len) {
    //         expand(s);
    //         new_ptr = ptr;
    //     } else {
    //         new_ptr = _recall_malloc(b, len);
    //     }
    // }
    return (new_ptr);
}