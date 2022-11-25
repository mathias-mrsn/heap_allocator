/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:27:12 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/25 15:29:59 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


#include "stdint.h"
#include "stddef.h"
#include "mem_block.h"


// extern mem_block * memory[3][2];

/*
    [TINY][BEGIN]->[...]->[TINY][END]
    [MEDIUM][BEGIN]->[...]->[MEDIUM][END]
    [LARGE][BEGIN]->[...]->[LARGE][END]
*/

# ifdef DEBUG
#   define LOG_ERROR(x) ft_putstr(x, 2);
#   define LOG(x)       ft_putstr(x, 1);
#   define PUTADDR(x)   ft_putaddr(x);
#   define PUTNBR(x)    ft_putnbr(x);
# else
#   define LOG_ERROR(x)
#   define LOG(x)
#   define PUTADDR(x)
#   define PUTNBR(x)
# endif


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

// void
// print_mem_block (mem_block *);

// void
// print_full_zone (const int zone );