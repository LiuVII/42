/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 22:59:18 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/29 22:59:19 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

void		ft_mapprint(char **map)
{
	int		i;

	i = -1;
	if (map)
		while (map[++i])
			ft_putendl(map[i]);
}

void		ft_mapfree(char ***map)
{
	int		i;

	i = -1;
	if (!map || !*map)
		return ;
	while ((*map)[++i])
	{
		free((*map)[i]);
		(*map)[i] = NULL;
	}
	free(*map);
	*map = NULL;
}

char		**ft_mapmake(int rows, int cols, char c)
{
	int		i;
	char	**map;

	map = (char**)malloc(sizeof(char*) * (rows + 1));
	if (!map)
		return (NULL);
	map[rows] = 0;
	i = -1;
	while (++i < rows)
	{
		map[i] = (char*)malloc(cols + 1);
		if (!map[i])
		{
			ft_mapfree(&map);
			return (NULL);
		}
		ft_memset(map[i], c, cols);
		map[i][cols] = '\0';
	}
	return (map);
}

void		ft_postomap(char *pos, int size, t_tet *tet_a)
{
	int		i;
	int		j;
	int		c;
	char	**map;

	map = ft_mapmake(size, size, '.');
	i = -1;
	while (pos[++i])
	{
		j = -1;
		c = 0;
		while (++j < 16)
		{
			if (tet_a[i][j / 4][j % 4] == '#')
			{
				map[(pos[i] - 1) / size + j / 4][(pos[i] - 1)
					% size + j % 4] = 65 + i;
				if (++c == 4)
					break ;
			}
		}
	}
	ft_mapprint(map);
	ft_mapfree(&map);
}
