/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:14:41 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/04 00:02:09 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

# define LARGE_REALLOC_CONDITION 2

void *
realloc_internal (
    void * ptr,
    const size_t len,
    const char * func,
    const char * file,
    const size_t line );

/*


    Every cases: (we assume that ptr and len are corrects)

    1: ptr is LARGE ok.

    2: we can just expand the size
        a: ptr is the last slot
        b: ptr 
    
    3: we have to recall malloc

    





*/

#define _REALLOC_ERR_IP(x) \
        error_printer(  x, \
                        "realloc()", \
                        "invalid pointer === cannot realloc a unknown address", \
                        m, \
                        (metadata){NULL, NULL, 0});

#define _REALLOC_ERR_DF(x) \
        error_printer(  x, \
                        "realloc()", \
                        "realloc freed pointer === this address cannot be reallocate", \
                        m, \
                        s->meta);

#define _REALLOC_ERR_MS(x) \
        error_printer(  x, \
                        "realloc()", \
                        "this pointer isn't at the begin of a slot === the entire slot has been freed", \
                        m, \
                        (metadata){NULL, NULL, 0});