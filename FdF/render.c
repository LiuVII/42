/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 21:49:14 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 21:49:15 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int		get_color(float zmin, float zmax, float zmean, float z)
{
	int		R;
	int		G;
	int		B;

	
	//printf("2 get color 2");
	G = (z > zmean) ? (int)((z - zmean) / (zmax - zmean) * 255) % 256 : 0;
	(z < zmean) ? (G = (int)((z - zmean) / (zmin - zmean) * 255) % 256) : 0;
	R = (z > zmean) ? 0 : G;
	B = (z < zmean) ? 0 : G;
	return (0x00FFFFFF - (R << 16) - (G << 8) - B);		
}

int		set_color(t_3d p1, t_3d p2, t_3d p, int flag)
{
	// int		R;
	// int		G;
	// int		B;

	p.z = p1.z;
	if (flag == 1)
		p.z += (p2.z - p1.z) * (p.x - p1.x) / (p2.x - p1.x);
	else if (flag == 2)
		p.z += (p2.z - p1.z) * (p.y - p1.y) / (p2.y - p1.y);
	// B = ((((int)p1.z) % 10) * 25) % 256;
	// G = (((((int)p1.z) % 100) / 10) * 256 * 25) % (256 * 256);
	// R = ((((int)p1.z) / 100) * 256 * 256 * 25) % (256 * 256 * 256);
	return (p.z);
}

void	ft_draw_line(t_data *data, t_3d p1, t_3d p2)
{
	t_3d p;
	t_2d a;
	t_2d b;
	float	dist;

	if ((p1.x > XS && p2.x > XS) || (p1.x < 0 && p2.x < 0) ||
		(p1.y > YS && p2.y > YS) || (p1.y < 0 && p2.y < 0))
		return ;
	p.x = p1.x/* - 0.1 * SIGN(p2.x - p1.x)*/;
	p.y = p1.y/* - 0.1 * SIGN(p2.y - p1.y)*/;
	dist = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	if (ABS(p2.x - p1.x) >= ABS(p2.y - p1.y) && ABS(p1.x - p2.x) / dist >= 0.001)
	{
		//printf("X DRAW LINE X %f", ABS(p1.x - p2.x));
		a.x = (p2.y - p1.y)/(p2.x - p1.x);
		b.x = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x);
		//printf("X DRAW LINE X");
		while ((p2.x - (p.x += (p2.x - p1.x) / dist)) * SIGN(p2.x - p1.x) >= 0)
		{
			//printf("0 0");
			mlx_pixel_put(data->mlx, data->win, p.x, a.x * p.x + b.x, set_color(p1, p2, p, 1));
		}
	}
	else if (ABS(p1.y - p2.y) / dist >= 0.001)
	{
		//printf("Y DRAW LINE Y %f", );
		a.y = (p2.x - p1.x)/(p2.y - p1.y);
		b.y = (p1.x * p2.y - p2.x * p1.y) / (p2.y - p1.y);
		while ((p2.y - (p.y += (p2.y - p1.y) / dist)) * SIGN(p2.y - p1.y) >= 0)
		{
			//printf("| Y: %f , Dist: %f , Diff: %f Abs : %f |", p.y, dist, p2.y - p1.y, ABS(p1.y - p2.y));
			mlx_pixel_put(data->mlx, data->win, a.y * p.y + b.y, p.y, set_color(p1, p2, p, 2));
		}
	}
}

t_3d	p_trans(t_data *data, t_3d p)
{
	t_3d	np;

	//np = ft_translate(ft_rotate(ft_scale(p, data->scale), data->phi, data->teta), data->O1);
	np = ft_zoom(ft_translate(ft_rotate(ft_scale(p, data->scale),
		data->phi, data->teta), data->O1), data->zoom, data->Oz);
	//np = ft_translate(ft_rotate(ft_zoom(p, data->zoom), data->phi, data->teta), data->O1);
	np.z = get_color(data->zmin, data->zmax, data->zmean, p.z);
	return (np);
}

void	ft_draw_image(t_data *data)
{
	int i;
	int j;
	int k;
	t_3d p1;

	mlx_clear_window(data->mlx, data->win);
	i = -1;
	while (++i < data->img_size.z && (j = -1))
		while (++j < data->img_size.y && (k = -1))
			while (++k < data->img_size.x)
			{
				//printf(" %d,%d,%d ", i , j, k);
				p1 = p_trans(data, data->image[i][j][k]);
				if (i > 0) 
					ft_draw_line(data, p1, p_trans(data, data->image[i - 1][j][k]));
				if (j > 0)
					ft_draw_line(data, p1, p_trans(data, data->image[i][j - 1][k]));
				if (k > 0)
					ft_draw_line(data, p1, p_trans(data, data->image[i][j][k - 1]));
				else if (k == 0 && j == 0 && i == 0)
					mlx_pixel_put(data->mlx, data->win, p1.x, p1.y, set_color(p1, p1, p1, 0));
			}
}

// void	ft_draw_point(t_data *data, float x, float y, float z)
// {
// 	mlx_pixel_put(data->mlx, data->win, p.x, a.x * p.x + b.x, 0x00FFFFFF);
// }

// void	image_transition(t_data *data)
// {
// 	int i;
// 	int j;
// 	int k;

// 	i = -1;
// 	while (++i < data->img_size.z && (j = -1))
// 		while (++j < data->img_size.y && (k = -1))
// 			while (++k < data->img_size.x)
// 				data->image[i][j][k] = ft_translate(ft_rotate(ft_scale(data->image[i][j][k], data->scale), data->phi, data->teta), data->O1);
// 	data->O1.x = 0;
// 	data->O1.y = 0;
// 	// data->Oz.x = XS / 2;
// 	// data->Oz.y = YS / 2;
// 	// data->zoom.x = 1;
// 	// data->zoom.y = 1;
// 	data->phi = 0;
// 	data->teta = 0;
// 	data->scale = 1;
// }

// int color;
// int R,G,B;
// R = (((int)(p.y - y1 + y0) * 3) % 255) * 255 * 255;
// G = (((((int)(p.y - y1 + y0)) / 10) * 3) % 255) * 255;
// B = ((int)(p.x - x1 + x0) * 3) % 255;
// color = R + G + B;

// float	ft_distance(float x0, float y0, float x1, float y1)
// {
// 	return ();
// }

// void	ft_draw_grid(t_data *data, int x0, int y0, int step, int rows, int cols)
// {
// 	// int x1;
// 	// int y1;
// 	int i;
// 	t_3d p;
// 	t_3d np;

// 	mlx_clear_window(data->mlx, data->win);
// 	i = -1;
// 	while (++i < rows * cols - 1)
// 	{
// 		// x1 = x0 + (i % cols) * step;
// 		// y1 = y0 + (i / rows) * step;
// 		p.x = (i % cols) * step;
// 		p.y = (i / rows) * step;
// 		p.z = (i % 2) * (step / 2);
// 		p = /*ft_zoom(*/ft_rotate(p, data->phi, data->teta)/*, data->zoom)*/;
// 		p.x += x0;
// 		p.y += y0;
// 		p = ft_zoom(p, data->zoom, data->Oz);
// 		if (i % cols + 1 < cols) 
// 		{
// 			np.x = (i % cols) * step + step;
// 			np.y = (i / rows) * step;
// 			np.z = ((i + 1) % 2) * (step / 2);
// 			np = /*ft_zoom(*/ft_rotate(np, data->phi, data->teta)/*, data->zoom)*/;
// 			np.x += x0;
// 			np.y += y0;
// 			np = ft_zoom(np, data->zoom, data->Oz);
// 			ft_draw_line(data, p.x, p.y, np.x, np.y);
// 		}
// 		if (i / rows + 1 < rows)
// 		{
// 			np.x = (i % cols) * step;
// 			np.y = (i / rows) * step + step;
// 			np.z = ((i + cols) % 2) * (step / 2);
// 			np = /*ft_zoom(*/ft_rotate(np, data->phi, data->teta)/*, data->zoom)*/;
// 			np.x += x0;
// 			np.y += y0;
// 			np = ft_zoom(np, data->zoom, data->Oz);
// 			ft_draw_line(data, p.x, p.y, np.x, np.y);
// 		}
// 	}
// }
