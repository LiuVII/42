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

int	ft_read(char *filename, t_data *data)
{
	int		ret;
	int		rows;
	int		fd;
	int		i;
	int		j;
	char	*line;
	t_list	*img_list;
	t_list	*tmp;
	char	**tab_line;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (-1);
	img_list = NULL;
	rows = 0;
	ret = -1;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		//printf("line %s\n", line);
		if (!img_list)
		{
			img_list = ft_lstnew(line, ft_strlen(line) + 1);
			tmp = img_list;
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
	if (!(data->image = (t_3d***)ft_memalloc(sizeof(t_3d**))))
		return (-1);
	data->img_size.z = 1;
	if (!((data->image)[0] = (t_3d**)ft_memalloc(sizeof(t_3d*) * rows)))
		return (-1);
	data->img_size.y = rows;
	i = -1;
	tmp = img_list;
	while (++i < rows)
	{
		//printf("%s\n", tmp->content);
		if (!(tab_line = ft_strsplit(tmp->content, ' ')))
			return (-1);
		if (!((data->image)[0][i] = (t_3d*)ft_memalloc(sizeof(t_3d) * tmp->content_size)))
			return (-1);
		j = -1;
		while (tab_line[++j])
		{
			//printf("%s ", tab_line[j]);
			(data->image)[0][i][j].z = ft_atoi(tab_line[j]);
			(data->image)[0][i][j].x = j * 10;
			(data->image)[0][i][j].y = i * 10;
			//printf("(%d, %d, %d)   ", (int)(data->image)[0][i][j].x, (int)(data->image)[0][i][j].y, (int)(data->image)[0][i][j].z);
		}
		//printf("\n");
		data->img_size.x = j;
		ft_mapfree(&tab_line);
		tmp = tmp->next;
	}
	return (0);	
}