/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 18:26:28 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/30 13:11:01 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

enum free_errors {
    INVALID_POINTER = 1,
    MIDDLE_OF_SLOT = 2,
    DOUBLE_FREE = 3,
    FREE_UNALLOCATED = 4
};

/**
 * @brief Free the memory allocated on the heap.
 * 
 * @param ptr Pointer to free
 */
void
free_internal (
    void * ptr );