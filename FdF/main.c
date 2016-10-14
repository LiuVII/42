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
#define XS 1024
#define YS 768


t_3d	ft_rotate(t_3d p, float phi, float teta)
{
	t_3d np;

	p.x = p.x - XS / 2;
	p.y = YS / 2 - p.y;
	np.x = cos(teta) * p.x - sin(teta) * p.z;
	np.y = cos(phi) * p.y - sin (phi) * p.z;
	np.z = sin(teta) * p.x + cos(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	np.x = np.x + XS / 2;
	np.y = YS / 2 - np.y;
	return (np);
}

void	ft_draw_line(t_data *data, float x0, float y0, float x1, float y1)
{
	t_3d p;
	t_3d np;
	int color;
	int R,G,B;
	float	phi;
	float	teta;

	phi = data->phi;
	teta = data->teta;
	p.x = x0 - 1;
	p.y = y0 - 1;
	p.z = 0;
	if (x0 != x1)
		while ((p.x += 1) <= x1)
		{
			p.y = (y1 - y0)/(x1 - x0) * p.x - (y1 * x0 - y0 * x1) / (x1 - x0);
			R = (((int)(p.y - y1 + y0) * 3) % 255) * 255 * 255;
			G = (((((int)(p.y - y1 + y0)) / 10) * 3) % 255) * 255;
			B = ((int)(p.x - x1 + x0) * 3) % 255;
			color = R + G + B;
			//p = ft_rotate(p, data->phi, data->teta);
			p.x = p.x - XS / 2;
			p.y = YS / 2 - p.y;
			np.x = cos(teta) * p.x - sin(teta) * p.z;
			np.y = cos(phi) * p.y - sin (phi) * p.z;
			np.z = sin(teta) * p.x + cos(teta) * (sin(phi) * p.y + cos (phi) * p.z);
			np.x = np.x + XS / 2;
			np.y = YS / 2 - np.y;
			mlx_pixel_put(data->mlx, data->win, np.x, np.y, color);
		}
	else
		while ((p.y += 1) <= y1)
		{
			p.x = x0;
			R = (((int)(p.y - y1 + y0) * 3) % 255) * 255 * 255;
			G = (((((int)(p.y - y1 + y0)) / 10) * 3) % 255) * 255;
			B = ((int)x0 * 3) % 255;
			color = R + G + B;
			//p = ft_rotate(p, data->phi, data->teta);
			p.x = p.x - XS / 2;
			p.y = YS / 2 - p.y;
			np.x = cos(teta) * p.x - sin(teta) * p.z;
			np.y = cos(phi) * p.y - sin (phi) * p.z;
			np.z = sin(teta) * p.x + cos(teta) * (sin(phi) * p.y + cos(phi) * p.z);
			np.x = np.x + XS / 2;
			np.y = YS / 2 - np.y;
			mlx_pixel_put(data->mlx, data->win, np.x, np.y, color);
		}
}

void	ft_draw_grid(t_data *data, int x0, int y0, int step, int rows, int cols)
{
	int x1;
	int y1;
	int i;

	mlx_clear_window(data->mlx, data->win);
	i = -1;
	while (++i < rows * cols)
	{
		x1 = x0 + (i % cols) * step;
		y1 = y0 + (i / rows) * step;
		if (i % cols + 1 < cols) 
			ft_draw_line(data, x1, y1, x1 + step, y1);
		if (i / rows + 1 < rows)
			ft_draw_line(data, x1, y1, x1, y1 + step);
	}
}

int	my_key_hook(int keycode, t_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	else if (keycode == 126)
		data->O1->y += 10;
	else if (keycode == 125)
		data->O1->y -= 10;
	else if (keycode == 123)
		data->O1->x += 10;
	else if (keycode == 124)
		data->O1->x -= 10;
	else if (keycode == 86)
		data->phi += 0.05;
	else if (keycode == 83)
		data->phi -= 0.05;
	else if (keycode == 87)
		data->teta += 0.05;
	else if (keycode == 84)
		data->teta -= 0.05;
	ft_draw_grid(data, data->O1->x, data->O1->y, 50, 2, 2);
	//printf ("key event %d\n", keycode);
	return (0);
}

int main(int argc, char **argv)
{
	t_data *data;

	data = (t_data*)malloc(sizeof(t_data));
	if (!(argc >= 1 && argv[0]))
		return (-1);
	if (!(data->mlx = mlx_init()))
	{
		fprintf(stderr, "An error occured whule initializing\n");
		return (-1);
	}
	if (!(data->win = mlx_new_window(data->mlx, XS, YS, "Welcome mortal!")))
	{
		fprintf(stderr, "An error occured whule creating window\n");
		return (-1);		
	}
	data->O1->x = 100;
	data->O1->y = 100;
	data->phi = 0;
	data->teta = 0;
	//color = 0x00FFFFFF;
	ft_draw_grid(data, data->O1->x, data->O1->y, 50, 2, 2);
	mlx_key_hook(data->win, my_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
