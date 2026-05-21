/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_specifier_2_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:50:26 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/18 17:11:41 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	hex_to_lower(va_list ap, t_data *data)
{
	char			*str;
	unsigned int	num;
	size_t			len;

	if (data->lsort)
		return(0);

	num = va_arg(ap, unsigned int);
	str = ntoa(data, (long long)num, 16);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}

int	hex_to_upper(va_list ap, t_data *data)
{
	char			*str;
	unsigned int	num;
	size_t			len;

	data->upper = 1;
	num = va_arg(ap, unsigned int);
	str = ntoa(data, (long long)num, 16);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	option_reset(data);
	return (len);
}

int	percent(int c, t_data *data)
{

	if (data->lsort)
		return(0);

	write(1, &c, 1);
	return (1);
}
