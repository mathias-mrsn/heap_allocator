/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_block.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:20:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/19 17:08:52 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "stddef.h"

typedef struct s_mem_block
{
    void    *ptr; // pointer + sizeof(s_mem_block)
    int     state; /* FULL, EMPTY, SOME_SPACE_FREE...*/
    size_t  size;
    size_t  space_used;
    struct s_mem_block * next;
    struct s_mem_block * prev;
}              mem_block;

enum {
    MEM_BEGIN,
    MEM_END
};

enum {
    EMPTY,
    FULL,
    SPACE_FREE
};

# define BLOCK_SIZE sizeof(mem_block)

int
add_block_front (mem_block *);

int
add_block_back (mem_block *);

mem_block *
create_block(const size_t, mem_block *, mem_block *);

/*
 [ ] Remove block from the list
 [ ] Find block with ...
*/