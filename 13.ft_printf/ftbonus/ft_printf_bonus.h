/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:14:28 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/18 18:34:40 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdio.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_data
{
	int	i;
	int	width;
	int	lsort;
	int	zsort;
	int	prec;
	int	sign;
	int	base;
	int	upper;
}		t_data;

int		ft_printf(const char *str, ...);
int		read_string(va_list ap, t_data *data, char *str, int read_byte);
int		specifier_check(va_list ap, t_data *data, char *str);
int		single_char(va_list ap, t_data *data);
int		string_char(va_list ap, t_data *data);
int		addr_to_hex(va_list ap, t_data *data);
int		integer(va_list ap, t_data *data);
int		unsigned_demical(va_list ap, t_data *data);
int		hex_to_lower(va_list ap, t_data *data);
int		hex_to_upper(va_list ap, t_data *data);
int		percent(int c, t_data *data);
size_t	ft_strlen(const char *str);
size_t	numlen(long long n, size_t nbase);
size_t	unumlen(unsigned long long n, size_t nbase);
char	*base_init(size_t nbase, size_t upper_flag);
char	*ntoa(t_data *data, long long n, size_t nbase);
char	*hex_addr(void *p);
int		option_check(t_data *data, char *str);
int		check_flag(t_data *data, char *str);
int		check_width(t_data *data, char *str);
int		check_precision(t_data *data, char *str);
int		ft_atoi(const char *str);
void	option_reset(t_data *data);
#endif
