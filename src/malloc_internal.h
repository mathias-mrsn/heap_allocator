/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:55:34 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 13:37:30 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"

/**
 * @brief Allocate N bytes of memory.
 */
void *
malloc_internal (
    size_t size,
    const char *func,
    const char *file,
    const int line );