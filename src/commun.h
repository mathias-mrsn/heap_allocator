/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:27:12 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/29 20:37:27 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdint.h"
#include "stddef.h"
#include "color.h"


// **
//  * @brief Defines to simplify the use of the attributes. 
//  * 
//  */
#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))
#define INLINE __attribute__((always_inline))

/*
    [TINY][BEGIN]->[...]->[TINY][END]
    [SMALL][BEGIN]->[...]->[SMALL][END]
    [LARGE][BEGIN]->[...]->[LARGE][END]
*/

#ifndef REALLOC_OLD_SLOT
#   define REALLOC_OLD_SLOT 1
#endif

# if (DEBUG == 1)
// #   define LOG_ERROR(x) ft_putstr(x, 2);
#   define MALLOC_DEBUG(x) ft_putstr(x"\n", 1);
#   define PUTSTR(x)    ft_putstr(x, 1);
#   define PUTADDR(x)   ft_putaddr(x);
#   define PUTNBR(x)    ft_putnbr(x);
# else
// #   define LOG_ERROR(x)
#   define MALLOC_DEBUG(x)
#   define PUTSTR(x)
#   define PUTADDR(x)
#   define PUTNBR(x)
# endif

#if (ABORT_IF_ERROR == true)
#   define WARNING(x)  \
        ft_putstr(BPURPLE, 2); \
        ft_putstr("Warning: ", 2); \
        ft_putstr(WHITE, 2); \
        ft_putstr(x, 2); \
        ft_putstr(RESET, 2);
#else
#   define WARNING(x) ERROR(x)
#endif

#define ERROR(x)  \
    ft_putstr(BRED, 2); \
    ft_putstr("Error: ", 2); \
    ft_putstr(WHITE, 2); \
    ft_putstr(x, 2); \
    ft_putstr(RESET, 2);


# ifdef __SIZEOF_INT128__
    typedef __int128_t	t_wide_int;
    typedef __uint128_t	t_uwide_int;
# else
    typedef intmax_t	t_wide_int;
    typedef uintmax_t	t_uwide_int;
# endif

#define PRIVATE static
#define SYSCALL_ERR -1

/* Memory */

void *
ft_memcpy (void *, const void *, size_t);

void *
ft_memset (void *, int, size_t);

/* Print */

void
ft_putstr (const char *, const int);

#define HEXA_LOWER "0123456789abcdef"
void
ft_putaddr (void *);

void
ft_putnbr (int64_t);