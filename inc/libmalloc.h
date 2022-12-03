/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:15:37 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 23:24:47 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"

#define malloc(x)   (__malloc(x, __func__, __FILE__, __LINE__))
#define free(x)     (__free(x, __func__, __FILE__, __LINE__))
#define realloc(x, y)   (__realloc(x, y, __func__, __FILE__, __LINE__))
#define calloc(x, y)    (__calloc(x, y, __func__, __FILE__, __LINE__))

void *
__calloc (
    size_t n,
    size_t s,
    const char * func,
    const char * file,
    const size_t line );

void *
__malloc (
    size_t size,
    const char * func,
    const char * file,
    const size_t line );

void
__free (
    void * ptr,
    const char * func,
    const char * file,
    const size_t line );

void *
__realloc (
    void * ptr,
    size_t size,
    const char * func,
    const char * file,
    const size_t line );

void
show_alloc_mem (void);

void
free_heap (void);
