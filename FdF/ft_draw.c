/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 22:56:04 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/18 22:56:06 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_color(float zmin, float zmax, float zmean, float z)
{
	int		R;
	int		G;
	int		B;

	G = (z > zmean) ? (int)((z - zmean) / (zmax - zmean) * 255) % 256 : 0;
	(z < zmean) ? (G = (int)((z - zmean) / (zmin - zmean) * 255) % 256) : 0;
	R = (z > zmean) ? 0 : G;
	B = (z < zmean) ? 0 : G;
	return (0x00FFFFFF - (R << 16) - (G << 8) - B);
}

int		set_color(t_3d p1, t_3d p2, t_3d p, int flag)
{
	p.z = p1.z;
	if (flag == 1)
		p.z += (p2.z - p1.z) * (p.x - p1.x) / (p2.x - p1.x);
	else if (flag == 2)
		p.z += (p2.z - p1.z) * (p.y - p1.y) / (p2.y - p1.y);
	return (p.z);
}

void	ft_draw_pixel(t_data *data, int x, int y, int c)
{
	int		i;
	long	mem;

	if (x < 0 || y < 0 || x > XS - 10 || y > YS - 10)
		return ;
	i = -1;
	mem = data->bpp / 8 * x + data->ls * y;
	while (i++ < data->bpp / 8 - 1)
	{
		data->img0[mem + i] = c % 256;
		c = c / 256;
	}
}

void	ft_draw_line(t_data *data, t_3d p1, t_3d p2)
{
	t_3d	p;
	t_2d	a;
	t_2d	b;
	float	dist;

	if ((p1.x > XS && p2.x > XS) || (p1.x < 0 && p2.x < 0) ||
		(p1.y > YS && p2.y > YS) || (p1.y < 0 && p2.y < 0))
		return ;
	p.x = p1.x;
	p.y = p1.y;
	dist = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	if (ABS(p2.x - p1.x) >= ABS(p2.y - p1.y) && ABS(p1.x - p2.x) / dist >= 0.01)
	{
		a.x = (p2.y - p1.y)/(p2.x - p1.x);
		b.x = (p1.y * p2.x - p2.y * p1.x) / (p2.x - p1.x);
		while ((p2.x - (p.x += (p2.x - p1.x) / dist)) * SIGN(p2.x - p1.x) >= 0)
			ft_draw_pixel(data, p.x, a.x * p.x + b.x, set_color(p1, p2, p, 1));
	}
	else if (ABS(p1.y - p2.y) / dist >= 0.01)
	{
		a.y = (p2.x - p1.x)/(p2.y - p1.y);
		b.y = (p1.x * p2.y - p2.x * p1.y) / (p2.y - p1.y);
		while ((p2.y - (p.y += (p2.y - p1.y) / dist)) * SIGN(p2.y - p1.y) >= 0)
			ft_draw_pixel(data, a.y * p.y + b.y, p.y, set_color(p1, p2, p, 2));
	}
}

int		ft_drawit(t_data *data)
{
	int		i;
	int		j;
	int		k;
	t_3d	p1;

	data->img = mlx_new_image(data->mlx, XS, YS);
	data->img0 = mlx_get_data_addr(data->img, &(data->bpp), &(data->ls), &(data->endian));
	i = -1;
	while (++i < data->img_size.z && (j = -1))
		while (++j < data->img_size.y && (k = -1))
			while (++k < data->img_size.x)
			{
				p1 = p_trans(data, data->image[i][j][k]);
				if (i > 0) 
					ft_draw_line(data, p1, p_trans(data, data->image[i - 1][j][k]));
				if (j > 0)
					ft_draw_line(data, p1, p_trans(data, data->image[i][j - 1][k]));
				if (k > 0)
					ft_draw_line(data, p1, p_trans(data, data->image[i][j][k - 1]));
				else if (k == 0 && j == 0 && i == 0)
					ft_draw_pixel(data, p1.x, p1.y, set_color(p1, p1, p1, 0));
			}
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}
