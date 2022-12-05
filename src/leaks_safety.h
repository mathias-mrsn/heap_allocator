/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_safety.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:09:03 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 14:43:29 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "bucket.h"
#include "commun.h"

# if (LEAK_SAFETY && !LEAKS)

void
leak_safety (void) DESTRUCTOR;

#else

void
leak_safety (void);

#endif