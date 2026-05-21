/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_1_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:30:07 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/19 12:31:52 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	long long	value;
	long long	minus;
	long long	temp;

	value = 0;
	minus = 1;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		temp = value;
		value = (value * 10) + (*str - '0');
		if (temp > value && minus == 1)
			return (-1);
		if (temp > value && minus == -1)
			return (0);
		str++;
	}
	return (value * minus);
}
