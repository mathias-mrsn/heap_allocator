/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:16:25 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 13:28:09 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_internal.h"
#include "free_internal.h"
#include "defragment_heap_internal.h"
#include "realloc_internal.h"
#include "show_alloc_mem_internal.h"
#include "leaks_internal.h"

#include "commun.h"
#include "leaks_safety.h"
#include <assert.h>

void *
__calloc (
    size_t n,
    size_t s,
    const char * func,
    const char * file,
    const size_t line )
{
    size_t bytes;
    void * ptr;

    if (n == 0 || s == 0)       {return (NULL);}
        
    bytes = n * s;
    if (bytes / s != n)         {return (NULL);}

    ptr = malloc_internal(bytes, func, file, line);
    if (ptr == NULL)            {return (NULL);}

    return (ptr);
}

void *
__malloc (
    size_t size,
    const char * func,
    const char * file,
    const size_t line )
{
    void * ptr;

    if (!size)                  {return (NULL);}
    
    ptr = malloc_internal(size, func, file, line);
    return (ptr);
}

void
__free (
    void * ptr,
    const char * func,
    const char * file,
    const size_t line )
{
    if (!ptr)                   {return ;}
    free_internal(ptr, func, file, line);
}

void
show_alloc_mem (void)
{
    show_alloc_mem_internal();
}

void *
__realloc (
    void * ptr,
    const size_t len,
    const char * func,
    const char * file,
    const size_t line )
{
    if (ptr && !len)        {free_internal(ptr, func, file, line);}
    else if (!ptr && len)   {return (malloc_internal(len, func, file, line));}
    else if (!ptr && !len)  {return (NULL);}
    else {
        return (realloc_internal(ptr, len, func, file, line));
    }
    return (NULL);
}

void
free_heap (void)
{
#if (LEAK_SAFETY == 1)
    WARNING(BWHITE"free_heap()"RESET" : LEAK_SAFETY is on, the program will be freed at the end automatically\n");
#endif
    leak_safety();
}

void
leaks (void) {
    leaks_internal();
}

// void
// defragment_heap (void) {
//     defragment_heap_internal();
// }
