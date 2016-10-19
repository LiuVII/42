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

// int		set_color(t_3d p1, t_3d p2, t_3d p, int flag)
// {
// 	// int		R;
// 	// int		G;
// 	// int		B;

// 	p.z = p1.z;
// 	if (flag == 1)
// 		p.z += (p2.z - p1.z) * (p.x - p1.x) / (p2.x - p1.x);
// 	else if (flag == 2)
// 		p.z += (p2.z - p1.z) * (p.y - p1.y) / (p2.y - p1.y);
// 	// B = ((((int)p1.z) % 10) * 25) % 256;
// 	// G = (((((int)p1.z) % 100) / 10) * 256 * 25) % (256 * 256);
// 	// R = ((((int)p1.z) / 100) * 256 * 256 * 25) % (256 * 256 * 256);
// 	return (p.z);
// }

t_2d	set_color(t_3dc p1, t_3dc p2, t_3d p, int flag)
{
	t_2d	c;
	// int		R;
	// int		G;
	// int		B;

	c.x = p1.p.z;
	c.y = p1.c;
	if (flag == 1)
		c.x += (p2.p.z - p1.p.z) * (p.x - p1.p.x) / (p2.p.x - p1.p.x);
	else if (flag == 2)
		c.x += (p2.p.z - p1.p.z) * (p.y - p1.p.y) / (p2.p.y - p1.p.y);
	if (flag == 1)
		c.y += (p2.c - p1.c) * (p.x - p1.p.x) / (p2.p.x - p1.p.x);
	else if (flag == 2)
		c.y += (p2.c - p1.c) * (p.y - p1.p.y) / (p2.p.y - p1.p.y);
	// B = ((((int)p1.z) % 10) * 25) % 256;
	// G = (((((int)p1.z) % 100) / 10) * 256 * 25) % (256 * 256);
	// R = ((((int)p1.z) / 100) * 256 * 256 * 25) % (256 * 256 * 256);
	return (c);
}

// void	ft_draw_line(t_data *data, t_3d p1, t_3d p2)
// {
// 	t_3d p;
// 	t_2d a;
// 	t_2d b;
// 	float	dist;

// 	if ((p1.x > XS && p2.x > XS) || (p1.x < 0 && p2.x < 0) ||
// 		(p1.y > YS && p2.y > YS) || (p1.y < 0 && p2.y < 0))
// 		return ;
// 	p.x = p1.x;
// 	p.y = p1.y;
// 	dist = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
// 	if (ABS(p2.x - p1.x) >= ABS(p2.y - p1.y) && ABS(p1.x - p2.x) / dist >= 0.001)
// 	{
// 		a.x = (p2.y - p1.y)/(p2.x - p1.x);
// 		b.x = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x);
// 		while ((p2.x - (p.x += (p2.x - p1.x) / dist)) * SIGN(p2.x - p1.x) >= 0)
// 			mlx_pixel_put(data->mlx, data->win, p.x, a.x * p.x + b.x, set_color(p1, p2, p, 1));
// 	}
// 	else if (ABS(p1.y - p2.y) / dist >= 0.001)
// 	{
// 		a.y = (p2.x - p1.x)/(p2.y - p1.y);
// 		b.y = (p1.x * p2.y - p2.x * p1.y) / (p2.y - p1.y);
// 		while ((p2.y - (p.y += (p2.y - p1.y) / dist)) * SIGN(p2.y - p1.y) >= 0)
// 			mlx_pixel_put(data->mlx, data->win, a.y * p.y + b.y, p.y, set_color(p1, p2, p, 2));
// 	}
// }

int	ft_mem_to_color(t_data *data, long mem)
{
	int i;
	int color;

	i = -1;
	color = 0;
	while (i++ < data->bpp / 8 - 1)
	{
		color *= 256;
		color = data->img0[mem + i];
	}
	return (color);
}

void		ft_draw_pixel(t_data *data, int x, int y, t_2d c)
{
	int i;
	long mem;
	int cx;
	int cy;

	if (x < 0 || y < 0 || x > XS - 10 || y > YS - 10)
		return ;
	i = -1;
	cx = c.x + 1000000000;
	//cx = -10000;
	cy = c.y;
	//printf("| %d, %d |", cx, cy);
	mem = data->bpp / 8 * x + data->ls * y;
	if (ft_mem_to_color(data, mem) < cx)
		while (i++ < data->bpp / 8 - 1)
		{
			data->img0[mem + i] = cx % 256;
			cx = cx / 256;
			data->img0c[mem + i] = cy % 256;
			cy = cy / 256;
		}
}

// void		ft_draw_pixel(t_data *data, int x, int y, int c)
// {
// 	int i;
// 	long mem;

// 	if (x < 0 || y < 0 || x > XS - 10 || y > YS - 10)
// 		return (0);
// 	i = -1;
// 	mem = data->bpp / 8 * x + data->ls * y;
// 	if (ft_mem_to_color(data, mem) < c)
// 		while (i++ < data->bpp / 8 - 1)
// 		{
// 			data->img0[mem + i] = c % 256;
// 			c = c / 256;
// 		}
// }

void	ft_draw_line(t_data *data, t_3dc p1, t_3dc p2)
{
	t_3d p;
	t_2d a;
	t_2d b;
	float	dist;

	if ((p1.p.x > XS && p2.p.x > XS) || (p1.p.x < 0 && p2.p.x < 0) ||
		(p1.p.y > YS && p2.p.y > YS) || (p1.p.y < 0 && p2.p.y < 0))
		return ;
	p.x = p1.p.x;
	p.y = p1.p.y;
	dist = sqrt((p1.p.x - p2.p.x) * (p1.p.x - p2.p.x) + (p1.p.y - p2.p.y) * (p1.p.y - p2.p.y));
	if (ABS(p2.p.x - p1.p.x) >= ABS(p2.p.y - p1.p.y) && ABS(p1.p.x - p2.p.x) / dist >= 0.01)
	{
		a.x = (p2.p.y - p1.p.y)/(p2.p.x - p1.p.x);
		b.x = (p1.p.y * p2.p.x - p2.p.y * p1.p.x) / (p2.p.x - p1.p.x);
		while ((p2.p.x - (p.x += (p2.p.x - p1.p.x) / dist)) * SIGN(p2.p.x - p1.p.x) >= 0)
			ft_draw_pixel(data, p.x, a.x * p.x + b.x, set_color(p1, p2, p, 1));
	}
	else if (ABS(p1.p.y - p2.p.y) / dist >= 0.01)
	{
		a.y = (p2.p.x - p1.p.x)/(p2.p.y - p1.p.y);
		b.y = (p1.p.x * p2.p.y - p2.p.x * p1.p.y) / (p2.p.y - p1.p.y);
		while ((p2.p.y - (p.y += (p2.p.y - p1.p.y) / dist)) * SIGN(p2.p.y - p1.p.y) >= 0)
			ft_draw_pixel(data, a.y * p.y + b.y, p.y, set_color(p1, p2, p, 2));
	}
}

float	ft_distance(t_3d p0, t_3d p1)
{
	return (sqrt((p0.x - p1.x) * (p0.x - p1.x) + (p0.y - p1.y) * (p0.y - p1.y)));
}

// t_3d	p_trans(t_data *data, t_3d p)
// {
// 	t_3d	np;

// 	//np = ft_translate(ft_rotate(ft_scale(p, data->scale), data->phi, data->teta), data->O1);
// 	np = ft_zoom(ft_translate(ft_rotate(ft_scale(p, data->scale),
// 		data->phi, data->teta), data->O1), data->zoom, data->Oz);
// 	//np = ft_translate(ft_rotate(ft_zoom(p, data->zoom), data->phi, data->teta), data->O1);
// 	//np.z = get_color(data->zmin, data->zmax, data->zmean, p.z);
// 	return (np);
// }

t_3dc	p_trans(t_data *data, t_3d p)
{
	t_3dc	np;

	np.p = ft_zoom(ft_translate(ft_rotate(ft_scale(p, data->scale),
		data->phi, data->teta), data->O1), data->zoom, data->Oz);
	np.c = get_color(data->zmin, data->zmax, data->zmean, p.z);
	return (np);
}

void	ft_draw_square(t_data *data, int i, int j, int k)
{
	t_3dc p11;
	t_3dc p22;
	t_3dc p0;
	t_3dc p1;
	t_3dc p2;
	t_3dc p3;
	t_2d a;
	t_2d b;
	float	rel;
	float	dist1;
	float	dist2;

	p0 = p_trans(data, data->image[i][j][k]);
	p1 = p_trans(data, data->image[i][j - 1][k]);
	p2 = p_trans(data, data->image[i][j][k - 1]);
	p3 = p_trans(data, data->image[i][j - 1][k - 1]);
	if ((p1.p.x > XS && p2.p.x > XS && p3.p.x > XS && p0.p.x > XS) || (p1.p.x < 0 && p2.p.x < 0 && p3.p.x < 0 && p0.p.x < 0) ||
		(p1.p.y > YS && p2.p.y > YS && p3.p.y > YS && p0.p.y > YS) || (p1.p.y < 0 && p2.p.y < 0 && p3.p.y < 0 && p0.p.y < 0))
		return ;
	p11 = p0;
	p22 = p1;
	dist1 = ft_distance(p0.p, p2.p);
	dist2 = ft_distance(p1.p, p3.p);
	if (dist1 >= dist2 && dist1 >= 0.01)
	{
		if (ABS(p2.p.x - p0.p.x) >= ABS(p2.p.y - p0.p.y) && ABS(p0.p.x - p2.p.x) / dist1 >= 0.01)
		{
			a.x = (p2.p.y - p0.p.y)/(p2.p.x - p0.p.x);
			b.x = (p0.p.y * p2.p.x - p2.p.y * p0.p.x) / (p2.p.x - p0.p.x);
			while ((p2.p.x - (p11.p.x += (p2.p.x - p0.p.x) / dist1)) * SIGN(p2.p.x - p0.p.x) >= 0)
			{
				p11.p.y = a.x * p11.p.x + b.x;
				rel = ft_distance(p11.p, p0.p) / dist1;
				p22.p.x = rel * (p3.p.x - p1.p.x) + p1.p.x;
				p22.p.y = rel * (p3.p.y - p1.p.y) + p1.p.y;
				p22.p.z = rel * (p3.p.z - p1.p.z) + p1.p.z;
				p22.c = rel * (p3.c - p1.c) + p1.c;
				ft_draw_line(data, p11, p22);
			}
		}
		else if (ABS(p0.p.y - p2.p.y) / dist1 >= 0.01)
		{
			a.y = (p2.p.x - p0.p.x)/(p2.p.y - p0.p.y);
			b.y = (p0.p.x * p2.p.y - p2.p.x * p0.p.y) / (p2.p.y - p0.p.y);
			while ((p2.p.y - (p11.p.y += (p2.p.y - p0.p.y) / dist1)) * SIGN(p2.p.y - p0.p.y) >= 0)
			{
				p11.p.x = a.y * p11.p.y + b.y;
				rel = ft_distance(p11.p, p0.p) / dist1;
				p22.p.x = rel * (p3.p.x - p1.p.x) + p1.p.x;
				p22.p.y = rel * (p3.p.y - p1.p.y) + p1.p.y;
				p22.p.z = rel * (p3.p.z - p1.p.z) + p1.p.z;
				p22.c = rel * (p3.c - p1.c) + p1.c;
				ft_draw_line(data, p11, p22);
			}	
		}
	}
	else if (dist2 >= 0.01)
	{
		if (ABS(p3.p.x - p1.p.x) >= ABS(p3.p.y - p1.p.y) && ABS(p1.p.x - p3.p.x) / dist2 >= 0.01)
		{
			a.x = (p3.p.y - p1.p.y)/(p3.p.x - p1.p.x);
			b.x = (p1.p.y * p3.p.x - p3.p.y * p1.p.x) / (p3.p.x - p1.p.x);
			while ((p3.p.x - (p22.p.x += (p3.p.x - p1.p.x) / dist2)) * SIGN(p3.p.x - p1.p.x) >= 0)
			{
				p22.p.y = a.x * p22.p.x + b.x;
				rel = ft_distance(p22.p, p1.p) / dist2;
				p11.p.x = rel * (p2.p.x - p0.p.x) + p0.p.x;
				p11.p.y = rel * (p2.p.y - p0.p.y) + p0.p.y;
				p11.p.z = rel * (p2.p.z - p0.p.z) + p0.p.z;
				p11.c = rel * (p2.c - p0.c) + p0.c;
				ft_draw_line(data, p11, p22);
			}
		}
		else if (ABS(p1.p.y - p3.p.y) / dist2 >= 0.01)
		{
			a.y = (p3.p.x - p1.p.x)/(p3.p.y - p1.p.y);
			b.y = (p1.p.x * p3.p.y - p3.p.x * p1.p.y) / (p3.p.y - p1.p.y);
			while ((p3.p.y - (p22.p.y += (p3.p.y - p1.p.y) / dist2)) * SIGN(p3.p.y - p1.p.y) >= 0)
			{
				p22.p.x = a.y * p22.p.y + b.y;
				rel = ft_distance(p22.p, p1.p) / dist2;
				p11.p.x = rel * (p2.p.x - p0.p.x) + p0.p.x;
				p11.p.y = rel * (p2.p.y - p0.p.y) + p0.p.y;
				p11.p.z = rel * (p2.p.z - p0.p.z) + p0.p.z;
				p11.c = rel * (p2.c - p0.c) + p0.c;
				ft_draw_line(data, p11, p22);
			}	
		}
	}
}

void	ft_draw_image(t_data *data)
{
	int i;
	int j;
	int k;
	t_3dc p1;

	data->img = mlx_new_image(data->mlx, XS, YS);
	data->img0 = mlx_get_data_addr(data->img, &(data->bpp), &(data->ls), &(data->endian));
	data->imgc = mlx_new_image(data->mlx, XS, YS);
	data->img0c = mlx_get_data_addr(data->imgc, &(data->bpp), &(data->ls), &(data->endian));
	i = -1;
	while (++i < data->img_size.z && (j = -1))
		while (++j < data->img_size.y && (k = -1))
			while (++k < data->img_size.x)
			{
				//printf(" %d,%d,%d ", i , j, k);
				p1 = p_trans(data, data->image[i][j][k]);
				if (i > 0) 
					ft_draw_line(data, p1, p_trans(data, data->image[i - 1][j][k]));
				if (j > 0 && k > 0)
					ft_draw_square(data, i, j, k);
				if (j > 0 && !k)
					ft_draw_line(data, p1, p_trans(data, data->image[i][j - 1][k]));
				if (k > 0 && !j)
					ft_draw_line(data, p1, p_trans(data, data->image[i][j][k - 1]));
				else if (k == 0 && j == 0 && i == 0)
					ft_draw_pixel(data, p1.p.x, p1.p.y, set_color(p1, p1, p1.p, 0));
			}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->imgc, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_image(data->mlx, data->imgc);
}

// void	ft_draw_image(t_data *data)
// {
// 	int i;
// 	int j;
// 	int k;
// 	t_3d p1;

// 	mlx_clear_window(data->mlx, data->win);
// 	i = -1;
// 	while (++i < data->img_size.z && (j = -1))
// 		while (++j < data->img_size.y && (k = -1))
// 			while (++k < data->img_size.x)
// 			{
// 				//printf(" %d,%d,%d ", i , j, k);
// 				p1 = p_trans(data, data->image[i][j][k]);
// 				if (i > 0) 
// 					ft_draw_line(data, p1, p_trans(data, data->image[i - 1][j][k]));
// 				if (j > 0)
// 					ft_draw_line(data, p1, p_trans(data, data->image[i][j - 1][k]));
// 				if (k > 0)
// 					ft_draw_line(data, p1, p_trans(data, data->image[i][j][k - 1]));
// 				else if (k == 0 && j == 0 && i == 0)
// 					mlx_pixel_put(data->mlx, data->win, p1.x, p1.y, set_color(p1, p1, p1, 0));
// 			}
// }

// float	ft_distance(float x0, float y0, float x1, float y1)
// {
// 	return ();
// }

