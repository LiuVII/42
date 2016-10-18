/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 22:00:05 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 22:00:06 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	ft_free_n_exit(t_data *data)
{
	int i;
	int j;

	mlx_destroy_window(data->mlx, data->win);
	i = -1;
	while (++i < data->img_size.z && (j = -1))
	{
		while (++j < data->img_size.y)
			free(data->image[i][j]);
		free(data->image[i]);
	}
	free(data->image);
	(data->mlx) ? free(data->mlx) : 0;
	exit(0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
		ft_free_n_exit(data);
	else if (keycode == 126)
		data->O1.y += 10;
	else if (keycode == 125)
		data->O1.y -= 10;
	else if (keycode == 123)
		data->O1.x += 10;
	else if (keycode == 124)
		data->O1.x -= 10;
	else if (keycode == 86)
		data->phi += 0.05;
	else if (keycode == 83)
		data->phi -= 0.05;
	else if (keycode == 87)
		data->teta += 0.05;
	else if (keycode == 84)
		data->teta -= 0.05;
	else if (keycode == 69)
		data->zoom *= 1.2;
	else if (keycode == 78)
		data->zoom /= 1.2;
	else if (keycode == 36)
	{
		printf ("X: %f, Y: %f\n", data->O1.x, data->O1.y);
		printf ("Phi: %f, Teta: %f\n", (data->phi * 180 / M_PI), (data->teta * 180 / M_PI));
		printf("Zoom: %f\n", data->zoom);
	}
	//ft_draw_grid(data, data->O1.x, data->O1.y, 50, 10, 10);
	ft_draw_image(data);
	//printf ("key event %d\n", keycode);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1 || button == 2)
	{
		data->O1.x += (XS / 2 - x) / data->zoom;
		data->O1.y += (YS / 2 - y) / data->zoom;
	}
	if (button == 5)
		data->zoom *= 1.2;
	else if (button == 4)
		data->zoom /= 1.2;
	//ft_draw_grid(data, data->O1.x, data->O1.y, 50, 10, 10);
	ft_draw_image(data);
	//data->O1.x += XS / 2 - data->Oz.x;
	//data->O1.y += YS / 2 - data->Oz.y;
	//printf ("mouse event %d\n", button);
	return (0);
}
