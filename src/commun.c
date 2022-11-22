/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:47:19 by mamaurai          #+#    #+#             */
/*   Updated: 2022/11/22 18:36:36 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include <unistd.h>

void *
ft_memcpy (
	void *dst,
	const void *src,
	size_t n )
{
	uint8_t			*s1;
	uint8_t			*s2;
	t_uwide_int		*us1;
	t_uwide_int		*us2;

	if ((!src && !dst) || dst == src)
		return (dst);
	us1 = (t_uwide_int *)dst;
	us2 = (t_uwide_int *)src;
	while (n >= sizeof(t_uwide_int))
	{
		*us1++ = *us2++;
		n -= sizeof(t_uwide_int);
	}
	s1 = (uint8_t *)us1;
	s2 = (uint8_t *)us2;
	while (n)
	{
		--n;
		*s1++ = *s2++;
	}
	return (dst);
}

PRIVATE
t_uwide_int
_int_to_wide_c (
	int c )
{
	t_uwide_int	new_c;
	uint8_t		shift_idx;

	shift_idx = 1;
	new_c = c;
	while (shift_idx < sizeof(t_uwide_int))
	{
		new_c = (new_c << 8) | new_c;
		shift_idx++;
	}
	return (new_c);
}

void	
*ft_memset (
	void *b,
	int c,
	size_t len )
{
	uint8_t				*s;
	t_uwide_int			*wide;
	const t_uwide_int	_c = _int_to_wide_c(c);

	if (!b)
		return (NULL);
	wide = (t_uwide_int *)b;
	while (len >= sizeof(t_uwide_int))
	{
		*wide++ = _c;
		len -= sizeof(t_wide_int);
	}
	s = (uint8_t *)wide;
	while (len--)
		*s++ = c;
	return (b);
}

PRIVATE
size_t
_ft_strlen (
	const char *str )
{
	size_t len = 0;
	for (; str[len]; len++);
	return len;
}

void
ft_putstr (
	const char *s,
	const int fd )
{
	if (!s)
		return ;
	write(fd, s, _ft_strlen(s));
}

void
ft_putaddr (
	void *addr)
{
	size_t	address;
	size_t	div;

	div = 16;
	address = (size_t)addr;
	write(1, "0x", 2);
	while (address / div > 15)
		div *= 16;
	while (div > 0)
	{
		write(1, &HEXA_LOWER[address / div], 1);
		address %= div;
		div /= 16;
	}
	write(1, "\n", 1);
}

PRIVATE
void
_ft_putchar (
	const char c )
{
	write(1, &c, 1);
}

void
ft_putnbr (
	int64_t n)
{
	uint64_t	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	if (n < 0)
		write(1, "-", 1);
	if (nb > 9)
		ft_putnbr(nb / 10);
	_ft_putchar(nb % 10 + 48);
}

void
print_mem_block (
	mem_block * block )
{
	ft_putstr("block->ptr: ", 1);
	ft_putaddr(block->ptr);
	ft_putstr("\nblock->zone_type : ", 1);
	ft_putnbr(block->zone_type);
	for (int i = 0; i < SLOT_BY_BLOCK; i++) {
		ft_putstr("\nblock->slot[", 1);
		ft_putnbr(i);
		ft_putstr("]: \n", 1);
		ft_putnbr(block->slots[i]);
	}
}

void
print_full_zone (
	const int zone )
{
	mem_block	*block;
	int			i;

	block = memory[zone][MEM_BEGIN];
	i = 0;
	LOG("print")
	while (block)
	{
		ft_putstr("\nblock[", 1);
		ft_putnbr(i);
		ft_putstr("]: \n", 1);
		print_mem_block(block);
		block = block->next;
		i++;
	}
	ft_putnbr(i);
}
