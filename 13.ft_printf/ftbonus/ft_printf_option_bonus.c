/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_data_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:34:30 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/17 16:21:36 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	check_flag(t_data *data, char *str)
{
	if (str[data->i] == '-')
		data->lsort = 1;
	else if (str[data->i] == '0')
		data->zsort = 1;
	else if (str[data->i] == '+' || str[data->i] == ' ')
	{
		if (data->sign != '+')
			data->sign = str[data->i];
	}
	else if (str[data->i] == '#')
		data->base = 1;
	else
		return (0);
	return (1);
}

int	check_width(t_data *data, char *str)
{
	int	num_len;

	if ('1' <= str[data->i] && str[data->i] <= '9')
		data->width = 1;
	else
		return (0);
	data->width = ft_atoi((const char *)&str[data->i]);
	num_len = numlen(data->width, 10);
	data->i += num_len;
	return (num_len);
}

int	check_precision(t_data *data, char *str)
{
	int	num_len;

	if (str[data->i] == '.')
		data->prec = 0;
	else
		return (0);
	data->prec = ft_atoi((const char *)&str[++data->i]);
	num_len = numlen(data->prec, 10);
	return (num_len);
}

int	option_check(t_data *data, char *str)
{
	while (check_flag(data, str))
		data->i++;
	check_width(data, str);
	//data->i += check_precision(data, str);
	return (1);
}

void	option_reset(t_data *data)
{
	data->width = 0;
	data->lsort = 0;
	data->zsort = 0;
	data->prec = -1;
	data->sign = 0;
	data->base = 0;
	data->upper = 0;
}
