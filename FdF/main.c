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

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (-1);
	if (!(argc >= 1 && argv[0]))
		return (-1);
	if (!(data->mlx = mlx_init()))
	{
		fprintf(stderr, "An error occured while initializing\n");
		return (-1);
	}
	if (!(data->win = mlx_new_window(data->mlx, XS, YS, "Welcome mortal!")))
	{
		fprintf(stderr, "An error occured while creating window\n");
		return (-1);		
	}
	data->O1.x = 100;
	data->O1.y = 100;
	data->Oz.x = XS / 2;
	data->Oz.y = YS / 2;
	data->zoom.x = 1;
	data->zoom.y = 1;
	data->phi = 0;
	data->teta = 0;
	data->scale = 5;
	//data->image = NULL;
	if (ft_read(argv[1], data) < 0)
	{
		fprintf(stderr, "An error occured while reading\n");
		return (-1);		
	}
	//color = 0x00FFFFFF;
	//ft_draw_grid(data, data->O1.x, data->O1.y, 50, 10, 10);
	ft_draw_image(data);
	mlx_mouse_hook(data->win, ft_mouse_hook, data);
	mlx_key_hook(data->win, ft_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
