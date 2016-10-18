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

int	ft_key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
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
	// else if (keycode == 69)
	// {
	// 	data->zoom.x += 0.2;
	// 	data->zoom.y += 0.2;
	// 	data->zoom.z += 0.2;
	// }
	// else if (keycode == 78)
	// {
	// 	data->zoom.x -= 0.2;
	// 	data->zoom.y -= 0.2;
	// 	data->zoom.z -= 0.2;
	// }
	else if (keycode == 36)
	{
		printf ("X: %f, Y: %f\n", data->O1.x, data->O1.y);
		printf ("Phi: %f, Teta: %f\n", (data->phi * 180 / M_PI), (data->teta * 180 / M_PI));
		printf("Zoom: %f\n", data->zoom.x);
	}
	//ft_draw_grid(data, data->O1.x, data->O1.y, 50, 10, 10);
	ft_draw_image(data);
	//printf ("key event %d\n", keycode);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		// data->Oz.x = x;
		// data->Oz.y = y;
		printf ("IN mouse X:%d Y: %d\n ", x, y);
		// data->zoom.x += 0.2;
		// data->zoom.y += 0.2;
	}
	else if (button == 2)
	{
		// data->Oz.x = x;
		// data->Oz.y = y;
		printf ("OUT mouse X:%d Y: %d\n ", x, y);
		// data->zoom.x -= (data->zoom.x > 0.2) ? 0.2: 0;
		// data->zoom.y -= (data->zoom.y > 0.2) ? 0.2: 0;
	}
	//ft_draw_grid(data, data->O1.x, data->O1.y, 50, 10, 10);
	ft_draw_image(data);
	//data->O1.x += XS / 2 - data->Oz.x;
	//data->O1.y += YS / 2 - data->Oz.y;
	//printf ("mouse event %d\n", button);
	return (0);
}
