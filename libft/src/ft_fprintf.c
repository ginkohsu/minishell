/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:15:33 by aloimusa          #+#    #+#             */
/*   Updated: 2025/06/13 22:15:36 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	specify(va_list *arg, char c, int fd);
static ssize_t	ft_putx_fd(uintptr_t n, char c, int fd);
static int		validate(const char *s);
static int		print(int fd, const char *s, size_t *i);

int	ft_fprintf(int fd, const char *format, ...)
{
	size_t	i;
	ssize_t	ret;
	ssize_t	len;
	va_list	arg;

	if (!validate(format))
		return (-1);
	i = 0;
	len = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i++] == '%')
			ret = specify(&arg, format[i++], fd);
		else
			ret = print(fd, format, &i);
		if (ret < 0)
		{
			va_end(arg);
			return (-1);
		}
		len += ret;
	}
	va_end(arg);
	return ((int)len);
}

int	print(int fd, const char *s, size_t *i)
{
	ssize_t	len;
	char	*ptr;

	len = 0;
	*i = *i - 1;
	ptr = (char *)&s[*i];
	while (s[*i] && s[*i] != '%')
	{
		*i = *i + 1;
		len++;
	}
	return (write(fd, ptr, len));
}

static int	validate(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		if (s[i++] == '%')
			if (!s[i] || !ft_strchr("cspdiuxX%", s[i++]))
				return (0);
	return (1);
}

static ssize_t	specify(va_list *arg, char c, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd((int)(va_arg(*arg, int)), fd));
	if (c == 's')
		return (ft_putstr_fd((char *)(va_arg(*arg, char *)), fd));
	if (c == 'd' || c == 'i')
		return (ft_putint_fd((int)(va_arg(*arg, int)), fd));
	if (c == 'u')
		return (ft_putuint_fd((unsigned int)(va_arg(*arg, unsigned int)), fd));
	if (c == 'p')
		return (ft_putx_fd((uintptr_t)(va_arg(*arg, void *)), c, fd));
	if (c == 'x' || c == 'X')
		return (ft_putx_fd((unsigned int)(va_arg(*arg, unsigned int)), c, fd));
	if (c == '%')
		return (write(fd, "%", 1));
	return (-1);
}

static ssize_t	ft_putx_fd(uintptr_t n, char c, int fd)
{
	char		*hex;
	char		array[18];
	short int	i;

	if (!n && c == 'p')
		return (write(fd, "(nil)", 5));
	if (!n)
		return (write(fd, "0", 1));
	if (c == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = 18;
	while (n > 0)
	{
		array[--i] = hex[n % 16];
		n = n / 16;
	}
	if (c == 'p')
	{
		array[--i] = 'x';
		array[--i] = '0';
	}
	return (write(fd, &array[i], 18 - i));
}
