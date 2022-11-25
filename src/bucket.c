/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bucket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:45:53 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/25 15:57:03 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bucket.h"
#include "commun.h"
#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

bucket *
new_bucket (
    zone_type zone)
{
    const size_t    size = TYPE_TO_SIZE(zone);
    bucket *bucket = (bucket *)mmap(NULL, sizeof(bucket), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

/*
// !\ BEWARE /!\\     
//PROJET DE SCORPION A NE PAS CORRIGER !!!!!!!!!!
*/
