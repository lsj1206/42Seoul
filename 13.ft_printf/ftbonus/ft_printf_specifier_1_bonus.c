/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifier_1_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:50:20 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/19 14:04:25 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	single_char(va_list ap, t_data *data)
{
	int	c;
	int	len;
	int	value;

	c = va_arg(ap, int);
	if (data->width)
		len = data->width;
	else
		len = 1;
	value = 0;
	if (data->lsort)
		value += write(1, &c, 1);
	while (--data->width > 0)
		value += write(1, " ", 1);
	if (!data->lsort)
		value += write(1, &c, 1);
	option_reset(data);
	if (value != len)
		return (-1);
	return (value);
}

int	string_char(va_list ap, t_data *data)
{
	char	*str;
	int		len;
	int		value;
	int		width;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	value = 0;
	if (data->prec > -1 && data->prec < len)
		len = data->prec;
	if (data->width && data->width > len)
		data->width = data->width - len;
	else
		data->width = 0;
	if (data->lsort)
		value += write(1, str, len);
	while (width--)
		value += write(1, " ", 1);
	if (!data->lsort)
		value += write(1, str, len);
	option_reset(data);
	return (value);
}

int	addr_to_hex(va_list ap, t_data *data)
{
	void				*p;
	char				*str;
	int					len;
	int					value;
	int					error_check;

	p = va_arg(ap, void *);
	str = hex_addr(p);
	len = ft_strlen(str);
	value = 0;
	if (data->width && data->width > len)
		data->width = data->width - len;
	else
		data->width = 0;
	error_check = data->width + len;
	if (data->lsort)
		value += write(1, str, len);
	while (data->width--)
		value += write(1, " ", 1);
	if (!data->lsort)
		value += write(1, str, len);
	option_reset(data);
	if (error_check != value)
		return (-1);
	return (value);
}

// int write_int(t_data *data, char *str, int len)
// {
// 	int	f_len;
// 	int	width;
// 	int	prec;
// 	if (data->width && data->width > len)
// }

// int	integer(va_list ap, t_data *data)
// {
// 	char	*str;
// 	int		len;
// 	int		value;

// 	value = va_arg(ap, int);
// 	str = ntoa(data, (long long)value, 10);
// 	len = ft_strlen(str);
// 	value = write_int(data, str, len);
// 	option_reset(data);
// 	free(str);
// 	return (value);
// }

int	integer(va_list ap, t_data *data)
{
	char	*str;
	int		num;
	int		len;
	int		value;
	int		blank;

	num = va_arg(ap, int);
	str = ntoa(data, (long long)num, 10);
	len = ft_strlen(str);
	value = 0;
	blank = 32;
	if (data->zsort && (!data->lsort || data->prec != -1))
		blank = 48;
	if (str[0] != '-' && data->sign)
		value += write(1, &data->sign, 1);
	if (data->width > -1 && data->width > len)
		data->width = data->width - len - value;
	else
		data->width = 0;
	if (data->lsort)
		value += write(1, str, len);
	while (data->width--)
		value += write(1, &blank, 1);
	if (!data->lsort)
		value += write(1, str, len);
	option_reset(data);
	free(str);
	return (value);
}

int	unsigned_demical(va_list ap, t_data *data)
{
	char			*str;
	unsigned int	num;
	size_t			len;

	if (data->lsort)
		return(0);

	num = va_arg(ap, unsigned int);
	str = ntoa(data, (long long)num, 10);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
