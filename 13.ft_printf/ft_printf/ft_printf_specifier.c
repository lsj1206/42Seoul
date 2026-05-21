/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:50:20 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/26 13:33:00 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	single_char(va_list ap)
{
	int	c;
	int	value;

	c = va_arg(ap, int);
	value = write(1, &c, 1);
	return (value);
}

int	string_char(va_list ap)
{
	char	*str;
	int		len;
	int		value;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	value = write(1, str, len);
	return (value);
}

int	addr_to_hex(va_list ap)
{
	void	*p;
	char	*str;
	int		len;
	int		value;

	p = va_arg(ap, void *);
	str = hex_addr(p);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	value = write(1, str, len);
	free(str);
	return (value);
}

int	integer(va_list ap)
{
	char	*str;
	int		num;
	int		len;
	int		value;

	num = va_arg(ap, int);
	str = ntoa((long long)num, 10, 0);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	value = write(1, str, len);
	free(str);
	return (value);
}

int	unsigned_to_char(va_list ap, size_t base, size_t upper_flag)
{
	char			*str;
	unsigned int	num;
	int				len;
	int				value;

	num = va_arg(ap, unsigned int);
	str = ntoa((long long)num, base, upper_flag);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	value = write(1, str, len);
	free(str);
	return (value);
}
