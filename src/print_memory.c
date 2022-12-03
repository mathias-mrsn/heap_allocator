/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 17:32:01 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 22:22:00 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Print_memory from my Piscine */

// TODO: Rework this function

#include <unistd.h>
#include "commun.h"
#include "color.h"

void
ft_printline(char *str, unsigned int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (str[i] >= ' ' && str[i] < 126)
			write(1, &str[i], 1);
		else
			write(1, ".", 1);
	}
	write(1, "\n", 1);
}

void
ft_printhex(unsigned char *str, unsigned int size)
{
	int		i;
	char	*base;

	base = "0123456789abcdef";
	i = -1;
	while (++i < size)
	{
		write(1, &base[str[i] / 16], 1);
		write(1, &base[str[i] % 16], 1);
		if (i % 2 == 1)
			write(1, " ", 1);
	}
	while (i < 16)
	{
		write(1, "  ", 2);
		if (i % 2 == 1)
			write(1, " ", 1);
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
		if (size - i < 16)
		{
			nb_char_to_print = size - i;
		}
		else
		{
			nb_char_to_print = 16;
		}
        ft_putstr(BWHITE, 2);
		ft_putaddr(addr + i, 2);
        ft_putstr(RESET, 2);
		write(1, ": ", 2);
		ft_printhex(addr + i, nb_char_to_print);
		ft_printline(addr + i, nb_char_to_print);
		i += 16;
	}
	return (0);
}