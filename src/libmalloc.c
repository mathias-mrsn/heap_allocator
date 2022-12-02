/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:16:25 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 17:43:51 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include "free_internal.h"
#include "defragment_heap_internal.h"
#include "realloc_internal.h"
#include "show_alloc_mem_internal.h"

#include "commun.h"
#include "leaks.h"
#include <assert.h>

void *
calloc (
    size_t n,
    size_t s )
{
    size_t bytes;
    void * ptr;

    if (n == 0 || s == 0)       {return (NULL);}
        
    bytes = n * s;
    if (bytes / s != n)         {return (NULL);}

    ptr = malloc_internal(bytes);
    if (ptr == NULL)            {return (NULL);}

    return (ptr);
}

void *
malloc (
    size_t size )
{
    void * ptr;

    if (!size)                  {return (NULL);}
    ptr = malloc_internal(size);
    return (ptr);
}

void
free (
    void * ptr )
{
    if (!ptr)                   {return ;}
    free_internal(ptr);
}

void
show_alloc_mem (void)
{
    show_alloc_mem_internal();
}

void
free_heap (void)
{
#if (LEAK_SAFETY == 1)
    WARNING("free_heap() : LEAK_SAFETY is on, the program will be freed at the end automatically\n");
#endif

    leak_safety();
}

void
defragment_heap (void) {
    defragment_heap_internal();
}

void *
realloc (
    void * ptr,
    const size_t len )
{
    if (ptr && !len)        {free_internal(ptr);}
    else if (!ptr && len)   {return (malloc_internal(len));}
    else if (!ptr && !len)  {return (NULL);}
    else {
        return (realloc_internal(ptr, len));
    }
    return (NULL);
}