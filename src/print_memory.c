/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:32:01 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/05 14:38:24 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Print_memory from my Piscine */

#include <unistd.h>
#include "commun.h"
#include "color.h"

#define HEXA "0123456789abcdef"

void
ft_printline(char *str, unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
        write(1, ((str[i] >= ' ' && str[i] < 126) ? &str[i] : "."), 1);
        i++;
	}
	write(1, "\n", 1);
}

void
ft_printhex(unsigned char *str, unsigned int size)
{
	size_t		i = 0;

	while (i < size)
	{
        if (str[i])
            ft_putstr(RED, 2);
		write(1, &HEXA[str[i] / 16], 1);
		write(1, &HEXA[str[i] % 16], 1);
        ft_putstr(RESET, 2);
		if (i % 2 == 1)
			write(1, " ", 1);
        i++;
	}
	while (i < 32)
	{
		write(1, ((i % 2 == 1) ? "   " : "  "), 2);
		i++;
	}
}

int	*
ft_print_memory(void *addr, unsigned int size)
{
	unsigned int		i;
	unsigned int		nb_char_to_print;

	i = 0;
	while (i < size)
	{
		if (size - i < 32)
		{
			nb_char_to_print = size - i;
		}
		else
		{
			nb_char_to_print = 32;
		}
        ft_putstr(BWHITE, 2);
		ft_putaddr(addr + i, 2);
        ft_putstr(RESET, 2);
		write(1, ": ", 2);
		ft_printhex(addr + i, nb_char_to_print);
		ft_printline(addr + i, nb_char_to_print);
		i += 32;
	}
	return (0);
}