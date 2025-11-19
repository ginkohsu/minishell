/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 06:17:07 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 07:32:13 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printf_flush(t_fprintf *f)
{
	ssize_t	wrote;

	if (f->len > 0)
	{
		wrote = write(f->fd, f->buffer, f->len);
		if (wrote == -1)
			f->ret = -1;
		else
			f->ret += wrote;
		f->len = 0;
	}
}

void	printf_putchar(t_fprintf *f, char c)
{
	if (f->ret == -1)
		return ;
	if (f->len >= PIPE_BUF)
		printf_flush(f);
	f->buffer[f->len++] = c;
}

void	printf_putstr(t_fprintf *f, char *s)
{
	char	*str;
	size_t	i;

	if (s)
		str = s;
	else
		str = "(null)";
	i = -1;
	while (str[++i])
		printf_putchar(f, str[i]);
}

void	printf_specify(t_fprintf *f, char spec, va_list *arg)
{
	if (spec == 'c')
		printf_putchar(f, va_arg(*arg, int));
	else if (spec == 's')
		printf_putstr(f, va_arg(*arg, char *));
	else if (spec == 'd' || spec == 'i')
		printf_putnbr(f, va_arg(*arg, int), 1);
	else if (spec == 'u')
		printf_putnbr(f, va_arg(*arg, unsigned int), 0);
	else if (spec == 'x')
		printf_puthex(f, va_arg(*arg, unsigned int), 0);
	else if (spec == 'X')
		printf_puthex(f, va_arg(*arg, unsigned int), 1);
	else if (spec == 'p')
		printf_putptr(f, va_arg(*arg, void *));
	else if (spec == '%')
		printf_putchar(f, '%');
	else if (spec == 'f')
		printf_putfloat(f, va_arg(*arg, double));
	else if (spec == 'l')
		printf_putnbr(f, va_arg(*arg, long long), 1);
}

ssize_t	ft_fprintf(int fd, const char *format, ...)
{
	t_fprintf	f;
	va_list		arg;
	size_t		i;

	i = 0;
	while (format[i])
		if (format[i++] == '%')
			if (!format[i] || !ft_strchr("cspdiuxX%fl", format[i++]))
				return (-1);
	f.fd = fd;
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
