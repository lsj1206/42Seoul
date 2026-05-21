/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:14:28 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/26 13:33:10 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *str, ...);
int		read_string(va_list ap, int i, char *str, int read_byte);
int		specifier_check(va_list ap, int i, char *str);
int		single_char(va_list ap);
int		string_char(va_list ap);
int		addr_to_hex(va_list ap);
int		integer(va_list ap);
int		unsigned_to_char(va_list ap, size_t base, size_t upper_flag);
size_t	ft_strlen(const char *str);
size_t	numlen(long long n, size_t nbase);
size_t	unumlen(unsigned long long n, size_t nbase);
char	*base_init(size_t nbase, size_t upper_flag);
char	*ntoa(long long n, size_t base_flag, size_t upper_flag);
char	*hex_addr(void *p);
#endif
