/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:48:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/13 14:48:18 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	displayit(t_data *data)
{
	ft_putstr("\
	____________________________\n\
	CONTROLS:\n\
	Translation:\n\
		Y: Key: UP, DOWN\n\
		X: Key: LEFT, RIGHT\n\n\
	Rotation:\n\
		X: Numpad: 1, 4\n\
		Y: Numpad: 2, 5\n\n\
	Zoom:\n\
		IN: Numpad: + | Mouse scroll\n\
		OUT: Numpad: -| Mouse scroll\n\n\
	Projections:\n\
		Elevation (init): E\n\
		Isometric: Key: I\n\n\
	Center:\n\
		Mouse click: Btn 1, Btn 2\n\
	____________________________\n\
	");
	//ft_drawit(data);
	mlx_expose_hook(data->win, ft_drawit, data);
	mlx_mouse_hook(data->win, ft_mouse_hook, data);
	mlx_key_hook(data->win, ft_key_hook, data);
	mlx_loop(data->mlx);	
}


void	ft_puterr_msg(int err)
{
	if (err == -1)
		ft_putendl("usage: .fdf/ $(FILENAME)");
	else if (err == -2)
		ft_putendl("error: mlx initializing failed");
	else if (err == -3)
		ft_putendl("error: window initializing failed");
	else if (err == -4)
		ft_putendl("error: while opening/reading a file");
	else if (err == -5)
		ft_putendl("error: memory allocation");
	else if (err == -10)
		ft_putendl("error: invalid map");
	else
		ft_putendl("error: unknown");
}

void	ft_free_n_exit(t_data *data, t_list **img_list, char *line, int err)
{
	int i;
	int j;

	(data && data->mlx && data->win) ? mlx_destroy_window(data->mlx, data->win) : 0;
	i = -1;
	if (data && data->image)
	{
		while (++i < data->img_size.z && (j = -1))
		{
			while (++j < data->img_size.y)
				free(data->image[i][j]);
			free(data->image[i]);
		}
		free(data->image);
	}
	(data && data->mlx) ? free(data->mlx) : 0;
	(data) ? free(data) : 0;
	(img_list && *img_list) ? ft_lstclr(img_list) : 0;
	(line) ? free(line) : 0;
	(err < 0) ? ft_puterr_msg(err) : 0;
	(err >= 0) ? exit(0) : exit(1);
}

void	data_init(t_data *data)
{
	data->O1.x = 100;
	data->O1.y = 100;
	data->Oz.x = XS / 2;
	data->Oz.y = YS / 2;
	data->zoom = 1;
	data->phi = 0;
	data->teta = 0;
	data->zmin = 1000;
	data->zmax = -1000;
	data->zmean = 0;
	data->scale.x = 25;
	data->scale.y = 25;
	data->scale.z = 25;
	data->image = NULL;
	data->img_size.x = 0;
	data->img_size.y = 0;
	data->img_size.z = 0;
}

int		main(int argc, char **argv)
{
	t_data *data;

	if (!(argc > 1 && argv[1]))
	{
		ft_puterr_msg(-1);
		return (1);
	}
	if (!(data = (t_data*)malloc(sizeof(t_data))))
	{
		ft_puterr_msg(-5);
		return (1);
	}
	data_init(data);
	if (!(data->mlx = mlx_init()))
		ft_free_n_exit(data, NULL, NULL, -2);
	if (!(data->win = mlx_new_window(data->mlx, XS, YS, argv[1])))
		ft_free_n_exit(data, NULL, NULL, -3);
	ft_read(argv[1], data);
	if (data->zmax > data->zmin) 
		data->scale.z = ((YS > XS) ? XS : YS) / (data->zmax - data->zmin) / 5;
	(data->img_size.x > 1) ? (data->scale.x = (XS) / data->img_size.x / 1.4) : 0;
	(data->img_size.y > 1) ? (data->scale.y = (YS) / data->img_size.y / 1.4) : 0;
	displayit(data);
	return (0);
}
