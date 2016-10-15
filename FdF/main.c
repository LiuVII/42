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
	np.x = cos(teta) * p.x - sin(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	np.y = cos(phi) * p.y - sin (phi) * p.z;
	np.z = sin(teta) * p.x + cos(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	np.x = np.x + XS / 2;
	np.y = YS / 2 - np.y;
	return (np);
}

t_3d	ft_zoom(t_3d p, t_3d zoom)
{
	t_3d np;

	np.x = XS / 2 + (p.x - XS / 2) * zoom.x;
	np.y = YS / 2 - (YS / 2- p.y) * zoom.y;
	np.z = p.z;
	return (np);
}


float	ft_distance(float x0, float y0, float x1, float y1)
{
	return (sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)));
}

void	ft_draw_line(t_data *data, float x0, float y0, float x1, float y1)
{
	t_3d p;
	int color;
	// int R,G,B;
	float	phi;
	float	teta;

	phi = data->phi;
	teta = data->teta;
	p.x = x0/* - 0.1 * SIGN(x1 - x0)*/;
	p.y = y0/* - 0.1 * SIGN(y1 - y0)*/;
	p.z = 0;
	if (x0 != x1 && ABS(x1 - x0) >= ABS(y1 - y0))
		while ((x1 - (p.x += (x1 - x0) / ft_distance(x0, y0, x1, y1))) * SIGN(x1 - x0) >= 0)
		{ 
			p.y = (y1 - y0)/(x1 - x0) * p.x - (y1 * x0 - y0 * x1) / (x1 - x0);
			// R = (((int)(p.y - y1 + y0) * 3) % 255) * 255 * 255;
			// G = (((((int)(p.y - y1 + y0)) / 10) * 3) % 255) * 255;
			// B = ((int)(p.x - x1 + x0) * 3) % 255;
			// color = R + G + B;
			color = 0x00FFFFFF;
			//p = ft_rotate(p, data->phi, data->teta);
			mlx_pixel_put(data->mlx, data->win, p.x, p.y, color);
		}
	else if (y0 != y1)
		while ((y1 - (p.y += (y1 - y0) / ft_distance(x0, y0, x1, y1))) * SIGN(y1 - y0) >= 0)
		{
			p.x = (x1 - x0)/(y1 - y0) * p.y - (x1 * y0 - x0 * y1) / (y1 - y0);
			// R = (((int)(p.y - y1 + y0) * 3) % 255) * 255 * 255;
			// G = (((((int)(p.y - y1 + y0)) / 10) * 3) % 255) * 255;
			// B = ((int)x0 * 3) % 255;
			// color = R + G + B;
			color = 0x00FFFFFF;
			//p = ft_rotate(p, data->phi, data->teta);
			mlx_pixel_put(data->mlx, data->win, p.x, p.y, color);
		}
}

void	ft_draw_grid(t_data *data, int x0, int y0, int step, int rows, int cols)
{
	// int x1;
	// int y1;
	int i;
	t_3d p;
	t_3d np;

	mlx_clear_window(data->mlx, data->win);
	i = -1;
	while (++i < rows * cols - 1)
	{
		// x1 = x0 + (i % cols) * step;
		// y1 = y0 + (i / rows) * step;
		p.x = (i % cols) * step;
		p.y = (i / rows) * step;
		p.z = 0;
		p = /*ft_zoom(*/ft_rotate(p, data->phi, data->teta)/*, data->zoom)*/;
		p.x += x0;
		p.y += y0;
		p = ft_zoom(p, data->zoom);
		if (i % cols + 1 < cols) 
		{
			np.x = (i % cols) * step + step;
			np.y = (i / rows) * step;
			np.z = 0;
			np = /*ft_zoom(*/ft_rotate(np, data->phi, data->teta)/*, data->zoom)*/;
			np.x += x0;
			np.y += y0;
			np = ft_zoom(np, data->zoom);
			ft_draw_line(data, p.x, p.y, np.x, np.y);
		}
		if (i / rows + 1 < rows)
		{
			np.x = (i % cols) * step;
			np.y = (i / rows) * step + step;
			np.z = 0;
			np = /*ft_zoom(*/ft_rotate(np, data->phi, data->teta)/*, data->zoom)*/;
			np.x += x0;
			np.y += y0;
			np = ft_zoom(np, data->zoom);
			ft_draw_line(data, p.x, p.y, np.x, np.y);
		}
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
		printf ("X: %f, Y: %f\n", data->O1->x, data->O1->y);
		printf ("Phi: %f, Teta: %f\n", (data->phi * 180 / M_PI), (data->teta * 180 / M_PI));
		printf("Zoom: %f\n", data->zoom.x);
	}
	ft_draw_grid(data, data->O1->x, data->O1->y, 50, 10, 10);
	//printf ("key event %d\n", keycode);
	return (0);
}

int	my_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1)
	{
		data->Oz.x = x;
		data->Oz.y = y;
		data->zoom.x += 0.2;
		data->zoom.y += 0.2;
	}
	else if (button == 2)
	{
		data->Oz.x = x;
		data->Oz.y = y;
		data->zoom.x -= (data->zoom.x > 0.2) ? 0.2: 0;
		data->zoom.y -= (data->zoom.y > 0.2) ? 0.2: 0;
	}
	ft_draw_grid(data, data->O1->x, data->O1->y, 50, 10, 10);
	//printf ("mouse event %d\n", button);
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
	data->zoom.x = 1;
	data->zoom.y = 1;
	data->phi = 0;
	data->teta = 0;
	//color = 0x00FFFFFF;
	ft_draw_grid(data, data->O1->x, data->O1->y, 50, 10, 10);
	mlx_mouse_hook(data->win, my_mouse_hook, data);
	mlx_key_hook(data->win, my_key_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
