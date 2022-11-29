/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:55:34 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/29 18:07:03 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"

/**
 * @brief Allocate N bytes of memory.
 * 
 * @param size The number of bytes to allocate.
 * @return void* Pointer to the slot of memory.
 */
void *
malloc_internal (
    size_t size );