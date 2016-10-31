/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 18:20:44 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/30 18:23:31 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_base(char *str, const char *base)
{
	int			sign;
	long long	num;
	int			len;
	int			digit;

	sign = 1;
	num = 0;
	len = ft_strlen(base);
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = 44 - *str;
		str++;
	}
	while ((digit = ft_strnchr(base, len, *str)) >= 0 && digit != len)
	{
		if ((num / 922337203685477580U == 1 && (digit >= 8 ||
			num % 922337203685477580U >= 1)) || (num / 922337203685477580U > 1))
			return ((-sign - 1) / 2);
		num *= len;
		num += digit;
		str++;
	}
	return (num * sign);
}
