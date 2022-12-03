/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:47:19 by mamaurai          #+#    #+#             */
/*   Updated: 2022/12/03 23:54:58 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commun.h"
#include "meta.h"
#include "print_memory.h"
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

void *	
ft_memset (
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
	const char *    s,
	const int       fd )
{
	if (!s)
		return ;
	write(fd, s, _ft_strlen(s));
}

void
ft_putaddr (
	void * addr,
    const int fd)
{
	size_t	address;
	size_t	div;

	div = 16;
	address = (size_t)addr;
	write(fd, "0x", 2);
	while (address / div > 15)
		div *= 16;
	while (div > 0)
	{
		write(fd, &HEXA_LOWER[address / div], 1);
		address %= div;
		div /= 16;
	}
}

PRIVATE
void
_ft_putchar (
	const char c,
    const int fd )
{
	write(fd, &c, 1);
}

void
ft_putnbr (
	int64_t n,
    const int fd)
{
	uint64_t	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	if (n < 0)
		write(fd, "-", 1);
	if (nb > 9)
		ft_putnbr(nb / 10, fd);
	_ft_putchar(nb % 10 + 48, fd);
}

void
error_printer (
    void * ptr,
    const char * func_name,
    const char * message,
    const metadata meta,
    const metadata meta2 )
{
    PUTERR("=================================================================\n")
    WARNING(func_name)
    PUTERR(": ")
    PUTERR(message)
    PUTERR("\n\n")
    if (ptr) {
        PUTERR("=== Memory freed ===\n\n")
        ft_print_memory(ptr, 128);
    } else {
        PUTERR("This address is not in the heap === ");
        PUTADDRR(ptr)
        PUTERR("\n");
    }
    PUTERR(BHCYAN"\nFunction called by >>> \n\t"YELLOWHB);
    PRINT_CALL_LOCATION(meta);
    if (meta2.file != NULL) {
        PUTERR(RESET BHCYAN"\n\nPreviously freed by >>> \n\t"YELLOWHB);
        PRINT_CALL_LOCATION(meta2);
    }
    PUTERR(RESET"\n=================================================================\n")
}