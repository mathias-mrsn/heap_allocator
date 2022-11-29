/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmalloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:15:37 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/29 18:36:41 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"

void *
calloc (
    size_t n,
    size_t s );

void *
malloc (
    size_t size );

void
free (
    void * ptr );

void
show_alloc_mem (void);