/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bit_fillit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 12:53:54 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/29 12:53:56 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

t_ull				g_tet[26];
char				g_bsol[27];
char				g_sol[27];
int					g_tnum;
int					g_size;
int					g_sol_n;

void		ft_placeit(int pos, int *ien, char *tet_u, t_ull *lmap)
{
	int				r;
	int				c;

	r = pos / g_size;
	c = pos % g_size;
	tet_u[ien[0]] = (!tet_u[ien[0]]) ? '1' : '\0';
	lmap[r / 4] ^= g_tet[ien[0]] << (c + 16 * (r % 4));
	if (r % 4 != 0)
		lmap[r / 4 + 1] ^= g_tet[ien[0]] >> (16 * (4 - r % 4) - c);
}

int			ft_bitfit_opt(int pos, char *tet_u, int *ien0, t_ull *lmap)
{
	int				ien[3];
	t_ull			tmp;

	tmp = 0;
	ien[1] = ien0[1];
	while (++pos < g_size * g_size)
	{
		if (!(pos % g_size) || !tmp)
			ft_map_reset(&tmp, lmap, pos / g_size, pos % g_size);
		ien[0] = -1;
		while (++ien[0] < g_tnum)
			if (!tet_u[ien[0]] && !(tmp & g_tet[ien[0]]))
			{
				ien[2] = ien0[2] - 1;
				ft_placeit(pos, ien, tet_u, lmap);
				g_sol[ien[0]] = pos + 1;
				if (ien[2] == 0 || ft_bitfit_opt(pos - 1, tet_u, ien, lmap))
					ft_solcompare(g_sol, g_bsol, g_tnum, &g_sol_n);
				ft_placeit(pos, ien, tet_u, lmap);
			}
		if (tmp % 2 == 0 && g_size * g_size < g_tnum * 4 + ++ien[1])
			return (0);
		tmp = tmp >> 1;
	}
	return (0);
}

int			ft_bitfit(int pos, char *tet_u, int *ien0, t_ull *lmap)
{
	t_ull			tmp;
	int				ien[3];

	ien[0] = -1;
	while (++ien[0] < g_tnum)
		if (!tet_u[ien[0]])
		{
			while (++pos < g_size * g_size)
			{
				if (!(pos % g_size) || !tmp)
					ft_map_reset(&tmp, lmap, pos / g_size, pos % g_size);
				if (!(tmp & g_tet[ien[0]]))
				{
					ien[2] = ien0[2] - 1;
					ft_placeit(pos, ien, tet_u, lmap);
					g_sol[ien[0]] = pos + 1;
					if (ien[2] == 0 || ft_bitfit(-1, tet_u, ien, lmap))
						return (1);
					ft_placeit(pos, ien, tet_u, lmap);
				}
				tmp = tmp >> 1;
			}
			return (0);
		}
	return (0);
}

void		global_init(int num, int size, char (*tet_u)[27], int *ien0)
{
	g_sol_n = 0;
	g_size = size;
	g_tnum = num;
	g_sol[num] = '\0';
	g_bsol[num] = '\0';
	(*tet_u)[num] = '\0';
	while (num--)
	{
		(*tet_u)[num] = '\0';
		g_sol[num] = '\0';
		g_bsol[num] = '\0';
	}
	ien0[0] = 0;
	ien0[1] = 0;
	ien0[2] = g_tnum;
}

int			ft_fill_main(int size, int num, t_tet *tet_a)
{
	char			tet_u[27];
	t_bit_map		map;
	int				ien0[3];

	global_init(num, size, &tet_u, ien0);
	while (num--)
		ft_tet_to_bit(&g_tet[num], tet_a[num]);
	ft_create_bitmap(g_size, &map);
	while (g_sol_n == 0)
	{
		if (g_size * g_size - 4 * g_tnum > 1)
		{
			g_sol_n = ft_bitfit(-1, tet_u, ien0, map);
			if (g_sol_n == 1 && g_sol_n--)
				ft_solcompare(g_sol, g_bsol, g_tnum, &g_sol_n);
		}
		else
			ft_bitfit_opt(-1, tet_u, ien0, map);
		if (g_sol_n == 0 && g_size++)
			ft_create_bitmap(g_size, &map);
	}
	ft_postomap(g_bsol, g_size, tet_a);
	return (0);
}
