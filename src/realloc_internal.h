/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:14:41 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/02 17:31:26 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

# define LARGE_REALLOC_CONDITION 2

void *
realloc_internal (
    void * ptr,
    const size_t len );

/*


    Every cases: (we assume that ptr and len are corrects)

    1: ptr is LARGE ok.

    2: we can just expand the size
        a: ptr is the last slot
        b: ptr 
    
    3: we have to recall malloc

    





*/