/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 22:41:33 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/22 22:41:35 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*new;
	long	num;
	long	i;
	long	trunc;

	i = 1;
	trunc = 10;
	(n < 0) ? i++ : 0;
	num = n;
	while ((num /= 10) && ++i)
		trunc *= 10;
	new = (char*)malloc(sizeof(char) * (i + 1));
	if (new)
	{
		new[i] = '\0';
		num = n;
		i = 0;
		(n < 0 && ++i) ? (num = -(long)(n)) : 0;
		(n < 0) ? new[0] = '-' : 0;
		while (((num %= trunc) + 1) && (trunc /= 10) >= 1 && ++i)
			new[i - 1] = num / trunc + '0';
		return (new);
	}
	return (NULL);
}
