/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 09:05:19 by exam              #+#    #+#             */
/*   Updated: 2016/10/18 09:33:05 by exam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa_base(int value, int base)
{
	const char	*basestr = "0123456789ABCDEF";
	long		num;
	long		sign;
	char		*str;
	int			i;

	i = 1;
	sign = 1;
	num = (value < 0) ? -1 * (long)value : value;
	if (value < 0 && base == 10 && i++)
		sign = -1;
	while ((num /= base) >= 1)
		i++;
	str = (char*)malloc(i + 1);
	str[i] = '\0';
	(value < 0 && base == 10) ? str[0] = '-' : 0;
	num = (value < 0) ? -1 * (long)value : value;
	while (i-- + (sign - 1) / 2)
	{
		str[i] = basestr[(num % base)];
		num /= base;
	}
	return (str);
}
