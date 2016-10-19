/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 21:48:16 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 21:48:18 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	set_mean(t_data *data)
{
	int 	i;
	int 	j;
	int 	k;
	double	sum;
	int		points;

	i = -1;
	points = 0;
	sum = 0;
	while (++i < data->img_size.z && (j = -1))
		while (++j < data->img_size.y && (k = -1))
			while (++k < data->img_size.x)
			{
				sum += data->image[i][j][k].z;
				points++;
			}
	return (sum / points);
}

static int	ft_read_to_list(int fd, t_list **img_list)
{
	t_list	*tmp;	
	char	*line;
	int		ret;
	int		rows;

	ret = -1;
	rows = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(*img_list))
		{
			*img_list = ft_lstnew(line, ft_strlen(line) + 1);
			tmp = *img_list;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(line, ft_strlen(line) + 1)))
				return (-1);
			tmp = tmp->next;		
		}
		rows++;
	}
	if (ret == -1)
		return (-1);
	return (rows);
}

static int	ft_split_n_rec(t_data *data, t_list *img_list, int rows)
{
	char	**tab_line;	
	int		i;
	int		j;

	i = -1;
	while (++i < rows)
	{
		if (!(tab_line = ft_strsplit(img_list->content, ' ')) ||
			!((data->image)[0][i] = (t_3d*)ft_memalloc(sizeof(t_3d) * img_list->content_size)))
			return (-1);
		j = -1;
		while (tab_line[++j])
		{
			(data->image)[0][i][j].z = ft_atoi(tab_line[j]);
			((data->image)[0][i][j].z > data->zmax) ? data->zmax = (data->image)[0][i][j].z : 0;
			((data->image)[0][i][j].z < data->zmin) ? data->zmin = (data->image)[0][i][j].z : 0;
			(data->image)[0][i][j].x = j;
			(data->image)[0][i][j].y = i;
		}
		data->img_size.x = j;
		ft_mapfree(&tab_line);
		img_list = img_list->next;
	}
	return (0);
}

int	ft_read(char *filename, t_data *data)
{
	int		rows;
	int		fd;
	t_list	*img_list;

	img_list = NULL;
	if ((fd = open(filename, O_RDONLY)) < 0 ||
		(rows = ft_read_to_list(fd, &img_list)) <= 0 ||
		!(data->image = (t_3d***)ft_memalloc(sizeof(t_3d**))))
		return (-1);
	data->img_size.z = 1;
	if (!((data->image)[0] = (t_3d**)ft_memalloc(sizeof(t_3d*) * rows)))
		return (-1);
	data->img_size.y = rows;
	if (ft_split_n_rec(data, img_list, rows) < 0)
		return (-1);
	data->zmean = set_mean(data);
	return (0);	
}
