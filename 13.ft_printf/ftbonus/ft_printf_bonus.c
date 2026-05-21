/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 18:10:39 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/19 14:01:51 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	specifier_check(va_list ap, t_data *data, char *str)
{
	int		value;

	value = 0;
	option_check(data, str);
	if (str[data->i] == 'c')
		value = single_char(ap, data);
	else if (str[data->i] == 's')
		value = string_char(ap, data);
	else if (str[data->i] == 'p')
		value = addr_to_hex(ap, data);
	else if (str[data->i] == 'd' || str[data->i] == 'i')
		value = integer(ap, data);
	else if (str[data->i] == 'u')
		value = unsigned_demical(ap, data);
	else if (str[data->i] == 'x')
		value = hex_to_lower(ap, data);
	else if (str[data->i] == 'X')
		value = hex_to_upper(ap, data);
	else if (str[data->i] == '%')
		value = percent(str[data->i], data);
	else
		return (-1);
	return (value);
}

int	read_string(va_list ap, t_data *data, char *str, int read_byte)
{
	int		value;

	value = 1;
	while (str[++data->i] != '\0')
	{
		if (str[data->i] == '%')
		{
			if (str[++data->i] == '\0')
				return (0);
			value = specifier_check(ap, data, str);
			if (value < 1)
				return (value);
			read_byte += value;
		}
		else
		{
			value = write(1, &str[data->i], 1);
			if (value == -1)
				return (value);
			read_byte++;
		}
	}
	return (read_byte);
}

int	ft_printf(const char *str, ...)
{
	int		read_byte;
	t_data	data;
	va_list	ap;

	read_byte = 0;
	data.i = -1;
	option_reset(&data);
	va_start(ap, str);
	read_byte = read_string(ap, &data, (char *)str, read_byte);
	if (read_byte == -1)
		return (-1);
	va_end(ap);
	return (read_byte);
}

int main (void)
{
	int	a = 1215;

	ft_printf("\n<A=%d>\n", ft_printf("%+11d", a));
	ft_printf("\n");
	printf("\n<B=%d>\n", printf("%+1.2d", a));
}
