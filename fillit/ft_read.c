/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/02 21:33:57 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/02 21:33:59 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"
#define BUFF_SIZE 550

char	g_var_tet[19][4][4] = {
	{ {"##.."}, {"##.."}, {"...."}, {"...."} },
	{ {"####"}, {"...."}, {"...."}, {"...."} },
	{ {"#..."}, {"#..."}, {"#..."}, {"#..."} },
	{ {"##.."}, {".#.."}, {".#.."}, {"...."} },
	{ {"..#."}, {"###."}, {"...."}, {"...."} },
	{ {"#..."}, {"#..."}, {"##.."}, {"...."} },
	{ {"###."}, {"#..."}, {"...."}, {"...."} },
	{ {"##.."}, {"#..."}, {"#..."}, {"...."} },
	{ {"###."}, {"..#."}, {"...."}, {"...."} },
	{ {".#.."}, {".#.."}, {"##.."}, {"...."} },
	{ {"#..."}, {"###."}, {"...."}, {"...."} },
	{ {"##.."}, {".##."}, {"...."}, {"...."} },
	{ {".#.."}, {"##.."}, {"#..."}, {"...."} },
	{ {".##."}, {"##.."}, {"...."}, {"...."} },
	{ {"#..."}, {"##.."}, {".#.."}, {"...."} },
	{ {"###."}, {".#.."}, {"...."}, {"...."} },
	{ {"#..."}, {"##.."}, {"#..."}, {"...."} },
	{ {".#.."}, {"###."}, {"...."}, {"...."} },
	{ {".#.."}, {"##.."}, {".#.."}, {"...."} },
};

t_tet		*ft_col_shift(t_tet *tet_a, int j)
{
	int		m;
	char	c;

	if (!tet_a)
		return (NULL);
	while (++j < 16)
		if ((*tet_a)[j % 4][j / 4] == '#')
		{
			m = j % 4;
			if (j-- / 4 > 0)
				while (++j < 16)
				{
					c = (*tet_a)[m % 4][m / 4];
					(*tet_a)[m % 4][m / 4] = (*tet_a)[j % 4][j / 4];
					(*tet_a)[j % 4][j / 4] = c;
					m++;
				}
			return (tet_a);
		}
	return (NULL);
}

t_tet		*ft_row_shift(t_tet *tet_a, int j)
{
	int		m;
	char	c;

	while (++j < 16)
		if ((*tet_a)[j / 4][j % 4] == '#')
		{
			m = j % 4;
			if (j-- / 4 > 0)
				while (++j < 16)
				{
					c = (*tet_a)[m / 4][m % 4];
					(*tet_a)[m / 4][m % 4] = (*tet_a)[j / 4][j % 4];
					(*tet_a)[j / 4][j % 4] = c;
					m++;
				}
			return (tet_a);
		}
	return (NULL);
}

t_tet		*ft_shift_n_check(t_tet **tet_a, int tn)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < tn)
	{
		if (!ft_col_shift(ft_row_shift((*tet_a) + i, -1), -1))
			return (NULL);
		j = -1;
		while (++j < 19 && (k = -1))
		{
			while (++k < 16)
				if ((*tet_a)[i][k / 4][k % 4] != g_var_tet[j][k / 4][k % 4])
					break ;
			if (k == 16)
				break ;
		}
		if (j == 19)
			return (NULL);
	}
	return ((*tet_a));
}

t_tet		*ft_str_to_arr(char *str, int tn)
{
	int		i;
	int		pos;
	int		ret;
	t_tet	*tet_a;

	i = -1;
	ret = 0;
	if (!(tet_a = (t_tet*)malloc(sizeof(t_tet) * tn)))
		return (NULL);
	while (++i < tn)
	{
		pos = -1;
		while (++pos < 16)
		{
			tet_a[i][pos / 4][pos % 4] = str[ret++];
			if (pos % 4 == 3 && str[ret++] != '\n')
				return (NULL);
			if (pos == 15 && ((i == tn - 1 && str[ret] != '\0')
				|| (i != tn - 1 && str[ret++] != '\n')))
			{
				return (NULL);
			}
		}
	}
	return (ft_shift_n_check(&tet_a, tn));
}

t_tet		*ft_read_file(int fd, int *tn)
{
	int		ret;
	char	*buff;
	t_tet	*tet_a;

	ret = 0;
	buff = (char*)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buff)
		return (NULL);
	if ((ret = read(fd, buff, BUFF_SIZE)) > 0 && (ret + 1) % 21 == 0)
	{
		*tn = (ret + 1) / 21;
		buff[ret] = '\0';
		tet_a = ft_str_to_arr(buff, *tn);
	}
	else
	{
		free(buff);
		return (NULL);
	}
	free(buff);
	return (tet_a);
}
