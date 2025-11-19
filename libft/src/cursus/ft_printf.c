/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 07:32:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 07:32:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printf_putptr(t_fprintf *f, void *ptr)
{
	unsigned long	addr;

	if (!ptr)
	{
		printf_putstr(f, "(nil)");
		return ;
	}
	addr = (unsigned long)ptr;
	printf_putstr(f, "0x");
	printf_puthex(f, addr, 0);
}

void	printf_putnbr(t_fprintf *f, unsigned long long n, int is_signed)
{
	if (is_signed && (long long)n < 0)
	{
		printf_putchar(f, '-');
		n = -(long long)n;
	}
	if (n >= 10)
		printf_putnbr(f, n / 10, 0);
	printf_putchar(f, (n % 10) + '0');
}

void	printf_puthex(t_fprintf *f, unsigned long n, int upper)
{
	const char	*base;

	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		printf_puthex(f, n / 16, upper);
	printf_putchar(f, base[n % 16]);
}

void	printf_putfloat(t_fprintf *f, double n)
{
	long long	integer;
	double		fractional;
	int			i;

	if (n < 0)
	{
		printf_putchar(f, '-');
		n = -n;
	}
	integer = (long long)n;
	fractional = n - integer;
	printf_putnbr(f, (unsigned long long)integer, 0);
	printf_putchar(f, '.');
	i = -1;
	while (++i < 6)
	{
		fractional *= 10;
		printf_putchar(f, '0' + (int)fractional);
		fractional -= (int)fractional;
	}
}

ssize_t	ft_printf(const char *format, ...)
{
	t_fprintf	f;
	va_list		arg;
	size_t		i;

	i = 0;
	while (format[i])
		if (format[i++] == '%')
			if (!format[i] || !ft_strchr("cspdiuxX%fl", format[i++]))
				return (-1);
	f.fd = STDOUT_FILENO;
	f.len = 0;
	f.ret = 0;
	va_start(arg, format);
	i = -1;
	while (format[++i] && f.ret != -1)
	{
		if (format[i] == '%')
			printf_specify(&f, format[++i], &arg);
		else
			printf_putchar(&f, format[i]);
	}
	va_end(arg);
	if (f.ret != -1)
		printf_flush(&f);
	return (f.ret);
}
