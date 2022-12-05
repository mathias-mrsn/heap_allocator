/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:26:28 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 13:53:00 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum free_errors {
    INVALID_POINTER = 1,
    MIDDLE_OF_SLOT = 2,
    DOUBLE_FREE = 3
};

/**
 * @brief Free the memory allocated on the heap.
 */
void
free_internal (
    void * ptr,
    const char * func,
    const char * file,
    const size_t line );

#if (CHECK_ALL)

#define _FREE_ERR_IP(x) \
        error_printer(  x, \
                        "free()", \
                        "invalid pointer === cannot free a unknown address", \
                        m, \
                        (metadata){NULL, NULL, 0});

#define _FREE_ERR_DF(x) \
        error_printer(  x, \
                        "free()", \
                        "double free === this address has already been freed", \
                        m, \
                        s->meta);

#define _FREE_ERR_MS(x) \
        error_printer(  x, \
                        "free()", \
                        "this pointer isn't at the begin of a slot === the entire slot has been freed", \
                        m, \
                        (metadata){NULL, NULL, 0});

#else

#define _FREE_ERR_IP(x) \
        error_printer(  x, \
                        "free()", \
                        "invalid pointer === cannot free a unknown address", \
                        (metadata){NULL, NULL, 0}, \
                        (metadata){NULL, NULL, 0});

#define _FREE_ERR_DF(x) \
        error_printer(  x, \
                        "free()", \
                        "double free === this address has already been freed", \
                        (metadata){NULL, NULL, 0}, \
                        (metadata){NULL, NULL, 0});

#define _FREE_ERR_MS(x) \
        error_printer(  x, \
                        "free()", \
                        "this pointer isn't at the begin of a slot === the entire slot has been freed", \
                        (metadata){NULL, NULL, 0}, \
                        (metadata){NULL, NULL, 0});

#endif