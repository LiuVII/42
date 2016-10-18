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


int main(int argc, char **argv)
{
	t_data *data;
	//char	*img_oo;
	//int		bpp;
	//int		ls;
	//int		endian;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (-1);
	if (!(argc > 1 && argv[1]))
		return (-1);
	if (!(data->mlx = mlx_init()))
	{
		fprintf(stderr, "An error occured while initializing\n");
		return (-1);
	}
	if (!(data->win = mlx_new_window(data->mlx, XS, YS, argv[1])))
	{
		fprintf(stderr, "An error occured while creating window\n");
		return (-1);		
	}
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
	if (ft_read(argv[1], data) < 0)
	{
		fprintf(stderr, "An error occured while reading\n");
		return (-1);		
	}
	if (data->zmax != data->zmin)
		data->scale.z = ((YS > XS) ? XS : YS) / (data->zmax - data->zmin) / 3;
	if (data->img_size.x != 1)
		data->scale.x = (XS) / data->img_size.x / 1.4;
	if (data->img_size.y != 1)
		data->scale.y = (YS) / data->img_size.y / 1.4;
	//color = 0x00FFFFFF;
	//ft_draw_grid(data, data->O1.x, data->O1.y, 50, 10, 10);
	ft_draw_image(data);
	//data->img = mlx_new_image(data->mlx, XS, YS);
	//img_oo = mlx_get_data_addr(data->img, &bpp, &ls, &endian);
	mlx_mouse_hook(data->win, ft_mouse_hook, data);
	mlx_key_hook(data->win, ft_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
