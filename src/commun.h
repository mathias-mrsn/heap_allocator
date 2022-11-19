/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:27:12 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/19 19:08:46 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pthread.h"
#include "stdint.h"
#include "stddef.h"
#include "mem_block.h"

extern pthread_mutex_t malloc_lock;
extern mem_block * edges[2];

# ifdef DEBUG
#   define LOG_ERROR(x) ft_putstr(x, 2);
#   define LOG(x) ft_putstr(x, 1);
#   define PUTADDR(x) printf("PUTADDR -> %p\n", x);
# else
#   define LOG_ERROR(x)
#   define LOG(x)
#   define PUTADDR(x)
# endif

#define THREAD_SAFETY_PRIORITY(x)                                   \
        if (pthread_mutex_##x (&malloc_lock) != 0) {                \
            LOG_ERROR("error: THREAD_SAFETY_PRIORITY failed\n");    \
            return NULL;                                            \
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

/* Memory */

void *
ft_memcpy (void *, const void *, size_t);

void *
ft_memset (void *, int, size_t);

/* Print */

void
ft_putstr(const char *, const int);

