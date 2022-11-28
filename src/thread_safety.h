/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safety.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:51:43 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/28 16:01:12 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pthread.h"
#include "unistd.h"

extern pthread_mutex_t malloc_lock;

#define THREAD_SAFETY(x)                                            \
        if (pthread_mutex_##x (&malloc_lock)) {                     \
            write(37, "error: THREAD_SAFETY failed\n", 2);          \
        }                                                           \

