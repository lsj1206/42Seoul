/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojulee <seojulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:08:58 by seojulee          #+#    #+#             */
/*   Updated: 2023/01/18 18:36:23 by seojulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

char	*base_init(size_t nbase, size_t upper_flag)
{
	char	*base;

	if (nbase == 8)
		base = "01234567";
	else if (nbase == 10)
		base = "0123456789";
	else if (nbase == 16 && !upper_flag)
		base = "0123456789abcdef";
	else if (nbase == 16 && upper_flag)
		base = "0123456789ABCDEF";
	else
		return (0);
	return (base);
}

size_t	numlen(long long n, size_t nbase)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n)
	{
		n /= nbase;
		len++;
	}
	return (len);
}

size_t	unumlen(unsigned long long n, size_t nbase)
{
	size_t	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= nbase;
		len++;
	}
	return (len);
}

char	*ntoa(t_data *data, long long n, size_t nbase)
{
	char	*base;
	char	*arr;
	size_t	len;
	int		minus;

	base = base_init(nbase, data->upper);
	len = numlen(n, nbase);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		return (0);
	arr[len] = '\0';
	minus = 0;
	if (n < 0)
	{
		n *= -1;
		minus = 1;
	}
	while (len)
	{
		arr[--len] = base[n % nbase];
		n /= nbase;
	}
	if (minus)
		arr[len] = '-';
	return (arr);
}

char	*hex_addr(void *p)
{
	unsigned long long	n;
	char				*base;
	char				*arr;
	size_t				len;

	n = (unsigned long long)p;
	base = "0123456789abcdef";
	len = unumlen(n, 16) + 2;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (arr == 0)
		return (0);
	arr[len] = '\0';
	while (len)
	{
		if (!n)
			break ;
		arr[--len] = base[n % 16];
		n /= 16;
	}
	arr[--len] = 'x';
	arr[--len] = '0';
	return (arr);
}
