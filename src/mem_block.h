/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:20:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/18 15:47:09 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"

typedef struct s_mem_block
{
    void    *ptr;
    int     state;
    size_t  size;
    struct s_mem_block * next;
    struct s_mem_block * prev;
}              mem_block;

enum {
    MEM_BEGIN,
    MEM_END
};

int
add_block_front (mem_block *);

int
add_block_back (mem_block *);

/*
 [ ] Remove block from the list
 [ ] Find block with ...
*/