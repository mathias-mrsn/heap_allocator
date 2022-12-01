/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_internal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:14:49 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 00:57:07 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "malloc_internal.h"
#include "free_internal.h"

PRIVATE
void *
_large_case(
    const bucket * b,
    size_t len )
{
    void * ptr = NULL;

    if ((ptr = malloc_internal(len)) == NULL) {
        return (NULL);
    }
    ft_memcpy(ptr, b->ptr, b->size_allocated);
    free_internal(b->ptr);
    return (ptr);
}

void *
realloc_internal (
    void * ptr,
    const size_t len )
{
    const bucket * b = find(ptr);
    void * new_ptr = NULL;
    
    if (b->zone == LARGE) {
        new_ptr = _large_case(b, len);
    } else {
        merge_freed_slots(b);
        /*
            1 : Expand the ptr
            2 : Free and malloc again
        */
    }
    return (NULL);
}