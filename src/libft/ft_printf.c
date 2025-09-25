/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinxu <jinxu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:18:36 by jinxu             #+#    #+#             */
/*   Updated: 2025/08/12 02:04:34 by jinxu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_conversion(char c, va_list *args, int *err);
static int	traverse_format(const char *format, va_list *args, int *err);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		err;

	if (!format)
		return (-1);
	va_start(args, format);
	err = 0;
	count = traverse_format(format, &args, &err);
	va_end(args);
	return (count);
}

static int	traverse_format(const char *format, va_list *args, int *err)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i] == '\0')
				return (-1);
			count += handle_conversion(format[i], args, err);
			if (count < 0 || *err)
				return (-1);
		}
		else
		{
			if (write(1, &format[i], 1) < 0)
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

static int	handle_conversion(char c, va_list *args, int *err)
{
	if (c == 'c')
		return (print_char(va_arg(*args, int), err));
	else if (c == 's')
		return (print_str(va_arg(*args, char *), err));
	else if (c == 'd' || c == 'i')
		return (print_nbr((long)va_arg(*args, int), err));
	else if (c == 'u')
		return (print_unsignedint(va_arg(*args, unsigned int), err));
	else if (c == 'x')
		return (print_hex(va_arg(*args, unsigned int), 0, err));
	else if (c == 'X')
		return (print_hex(va_arg(*args, unsigned int), 1, err));
	else if (c == 'p')
		return (print_ptr((uintptr_t)va_arg(*args, void *), err));
	else if (c == '%')
	{
		if (write(1, "%", 1) < 0)
			*err = 1;
		return (1);
	}
	*err = 1;
	return (-1);
}
/*
*	if % followed by undefined char or
*	'%' at end of format string with no specifier:
*	undefined behavior, we return -1 to
*	indicate the error.
*/
