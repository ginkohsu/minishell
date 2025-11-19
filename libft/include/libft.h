/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloimusa <aloimusa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:00:00 by aloimusa          #+#    #+#             */
/*   Updated: 2025/11/14 08:00:00 by aloimusa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <limits.h>
# include <stdbool.h>

# ifndef BUFFERSIZE
#  define BUFFERSIZE 42
# endif

typedef struct s_fprintf
{
	char	buffer[PIPE_BUF];
	int		fd;
	size_t	len;
	ssize_t	ret;
}	t_fprintf;

/* stock functions */
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *src, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, const char *set);
char		**ft_split(char const *s, char c);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strnstr(const char *s, const char *f, size_t n);

/* str_tools functions */
char		*ft_strapp(char *s1, const char *s2);
char		*ft_strprep(const char *s1, char *s2);
long		ft_atol(const char *str);
long long	ft_atoll(const char *str);
double		ft_atod(const char *s, char **endptr);
char		*ft_itoa_base(unsigned long n, char *base);

/* arr_tools functions */
size_t		arrlen(char **arr);
size_t		arrlcpy(char **dst, char **src, size_t dstsize);
char		**arrdup(char **src);
char		**arrndup(char **src, size_t n);
char		**arrstr(char **arr, const char *str);
char		**arrstrn(char **arr, const char *str, size_t n);
void		arrsort(char **arr);
void		free_array(char **arr);

/* cursus functions */
char		*get_next_line(int fd);
ssize_t		ft_printf(const char *format, ...);
ssize_t		ft_fprintf(int fd, const char *format, ...);

/* printf helper functions */
void		printf_flush(t_fprintf *f);
void		printf_putchar(t_fprintf *f, char c);
void		printf_putstr(t_fprintf *f, char *s);
void		printf_putnbr(t_fprintf *f, unsigned long long n, int is_signed);
void		printf_puthex(t_fprintf *f, unsigned long n, int upper);
void		printf_putptr(t_fprintf *f, void *ptr);
void		printf_putfloat(t_fprintf *f, double n);
void		printf_specify(t_fprintf *f, char spec, va_list *arg);

/* additional stock helpers */
int			ft_isdigit(int c);

/* minishell functions */
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_putnbr_fd(int n, int fd);
char		*ft_strjoin_safe(char const *s1, char const *s2);
size_t		ft_strlen_z(const char *s);
int			print_char(int c, int *err);
int			print_hex(unsigned int n, int is_upper, int *err);
int			print_nbr(long nbr, int *err);
int			print_ptr(uintptr_t ptr, int *err);
int			print_str(char *str, int *err);
int			print_unsignedint(unsigned int nbr, int *err);

#endif
