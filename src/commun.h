/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:27:12 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 23:54:37 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stdint.h"
#include "stddef.h"
#include "color.h"
#include "meta.h"


// **
//  * @brief Defines to simplify the use of the attributes. 
//  * 
//  */
#define UNUSED __attribute__((unused))
#define PACKED __attribute__((packed))
#define CONSTRUCTOR __attribute__((constructor))
#define DESTRUCTOR __attribute__((destructor))
#define INLINE __attribute__((always_inline))
#define NONNULL __attribute__((nonnull))

# if (DEBUG == 1)
#   define MALLOC_DEBUG(x) ft_putstr(x"\n", 1);
# else
#   define MALLOC_DEBUG(x)
# endif

#define WARNING(x)  \
        ft_putstr(BPURPLE, 2); \
        ft_putstr("Warning: "RESET, 2); \
        ft_putstr(BWHITE, 2); \
        ft_putstr(x, 2); \
        ft_putstr(RESET, 2);

# define PRINT_CALL_LOCATION(m) \
        PUTERR(m.file); \
        PUTERR(":"); \
        PUTNBRR(m.line); \
        PUTERR(" in "); \
        PUTERR(m.func);

#define PUTSTR(x)    ft_putstr(x, 1);
#define PUTADDR(x)   ft_putaddr(x, 1);
#define PUTADDRR(x)   ft_putaddr(x, 2);
#define PUTNBR(x)    ft_putnbr(x, 1);
#define PUTNBRR(x)   ft_putnbr(x, 2);
#define PUTERR(x)    ft_putstr(x, 2);

// #define ERROR(x)  \
//     ft_putstr(BRED, 2); \
//     ft_putstr("Error: ", 2); \
//     ft_putstr(WHITE, 2); \
//     ft_putstr(x, 2); \
//     ft_putstr(RESET, 2); \


# ifdef __SIZEOF_INT128__
    typedef __int128_t	t_wide_int;
    typedef __uint128_t	t_uwide_int;
# else
    typedef intmax_t	t_wide_int;
    typedef uintmax_t	t_uwide_int;
# endif

#define PRIVATE static
#define SYSCALL_ERR -1
#define SUCCESS 0
#define FAILURE 1

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
ft_putaddr (void *, const int fd);

void
ft_putnbr (int64_t, const int);

void
error_printer (
    void * ptr,
    const char * func_name,
    const char * message,
    const metadata meta,
    const metadata meta2 );