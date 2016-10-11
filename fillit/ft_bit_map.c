/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 14:01:34 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/05 14:01:37 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void		ft_map_reset(t_ull *tmp, t_ull *lmap, int r, int c)
{
	*tmp = lmap[r / 4] >> (16 * (r % 4));
	if (r % 4 != 0)
		*tmp += lmap[r / 4 + 1] << (16 * (4 - r % 4));
	*tmp = *tmp >> c;
}

void		ft_tet_to_bit(t_ull *ll, t_tet tet)
{
	int			i;
	int			j;
	t_ull		m;

	i = -1;
	*ll = 0;
	m = 1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 16)
		{
			if (j < 4 && tet[i][j] == '#')
				*ll += m;
			m *= 2;
		}
	}
}

void		ft_solcompare(char *str1, char *str2, int tnum, int *sol)
{
	int				i;
	int				j;

	(*sol)++;
	i = -1;
	while (str1[++i])
		if (str2[i] != str1[i])
		{
			if ((*sol) == 1 || str2[i] > str1[i])
			{
				j = -1;
				while (++j < tnum)
					str2[j] = str1[j];
			}
			return ;
		}
}

t_ull		ft_get_start_bits(unsigned char size)
{
	t_ull			total;
	unsigned char	i;

	total = 0;
	i = 0;
	while (i++ < size)
	{
		total = total << 1;
		total += 1;
	}
	return (total);
}

void		ft_create_bitmap(unsigned char size, t_bit_map *map)
{
	t_ull		total;
	int			i;
	int			j;

	j = 0;
	while (j < 4)
		(*map)[j++] = 0;
	total = ft_get_start_bits(size);
	i = 0;
	j = 0;
	while (i++ < size)
	{
		(*map)[j] = (*map)[j] << 16ul;
		(*map)[j] += total;
		if (i % 4 == 0)
			j++;
	}
	j = -1;
	while (++j < 4)
		(*map)[j] = ~((*map)[j]);
}
