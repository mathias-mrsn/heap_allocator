/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:26:55 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/28 18:28:52 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "malloc_family.h"

void *
calloc (
    size_t n,
    size_t s )
{
    size_t bytes;
    void * ptr;

    if (n == 0 || s == 0)
        return (NULL);
        
    bytes = n * s;
    if (bytes / s != n)
        return (NULL);

    ptr = malloc(bytes);
    if (ptr == NULL)
        return (NULL);

    return (ptr);
}