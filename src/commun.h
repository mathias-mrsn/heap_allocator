/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:27:12 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/18 16:21:05 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pthread.h"
#include "stdint.h"
#include "stddef.h"
#include "mem_block.h"

static mem_block * edges[2];
static pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;

#define THREAD_SAFETY_PRIORITY(x)                       \
        if (pthread_mutex_##x (&malloc_lock) != 0) {    \
            return NULL;                                \
        }

# ifdef __SIZEOF_INT128__
    typedef __int128_t	t_wide_int;
    typedef __uint128_t	t_uwide_int;
# else
    typedef intmax_t	t_wide_int;
    typedef uintmax_t	t_uwide_int;
# endif

enum {
    SMALL_ZONE = 1024,
    MEDIUM_ZONE = 2048,
    LARGE_ZONE = 4096
};

#define PRIVATE static

void *
memcpy (void *, const void *, size_t);

void *
memset (void *, int, size_t);