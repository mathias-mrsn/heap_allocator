/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:33:51 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/27 19:41:24 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_memory.h"

static void	ft_printline(char *str, unsigned int size)
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

static void	ft_putaddr(void *addr)
{
	char	addr_c[16];
	long	addr_l;
	int		i;

	addr_l = (long)addr;
	i = 0;
	while (addr_l > 0)
	{
		addr_c[i] = addr_l % 16;
		if (addr_c[i] < 10)
			addr_c[i] += '0';
		else
			addr_c[i] += 87;
		addr_l = addr_l / 16;
		i++;
	}
	while (i < 16)
	{
		addr_c[i] = '0';
		i++;
	}
	while (--i >= 0)
		write(1, &addr_c[i], 1);
}

static void	ft_printhex(unsigned char *str, unsigned int size)
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

int	ft_print_memory(void *addr, unsigned int size)
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
		ft_putaddr(addr + i);
		write(1, ": ", 2);
		ft_printhex(addr + i, nb_char_to_print);
		ft_printline(addr + i, nb_char_to_print);
		i += 16;
	}
	return (0);
}