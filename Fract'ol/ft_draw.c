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

#include "fractol.h"
#include <stdio.h>

float	z_dist(float x, float y)
{
	return (sqrt(ABS(x * x - y * y)));
}

int		get_color(float zmin, float zmax, float zmean, float z)
{
	int		r;
	int		g;
	int		b;

	g = (z > zmean) ? (int)((z - zmean) / (zmax - zmean) * 255) % 256 : 0;
	(z < zmean) ? (g = (int)((z - zmean) / (zmin - zmean) * 255) % 256) : 0;
	r = (z > zmean) ? 0 : g;
	b = (z < zmean) ? 0 : g;
	return (0x00FFFFFF - (r << 16) - (g << 8) - b);
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

void	ft_draw_pixel(t_data *d, int x, int y, int c)
{
	int		i;
	long	mem;

	if (x < 0 || y < 0 || x > XS - 10 || y > YS - 10)
		return ;
	i = -1;
	mem = d->bpp / 8 * x + d->ls * y;
	while (i++ < d->bpp / 8 - 1)
	{
		d->img_p0[mem + i] = c % 256;
		c = c / 256;
	}
}

void 	draw_mandelset(t_data *d)
{
	t_3d	c;
	t_2d	z;
	t_2d	z1;
	t_2d	p;
	int		color;

	p.y = -1;
	c.z = 0;
	while (++p.y <= YS && (p.x = -1))
		while (++p.x <= XS)
		{
			c.x = 3.5 * ((p.x - XS / 2) / d->zoom + XS / 2 - d->o1.x) / XS;
			c.y = 3.5 * ((p.y - YS / 2) / d->zoom + YS / 2 - d->o1.y) / YS;
			z.x = 0;
			z.y = 0;
			color = -1;
			while (++color < 500 && ABS(z.x * z.x - z.y * z.y) <= 4)
			{
				z1.x = (z.x * z.x - z.y * z.y) + c.x;
				z.y = 2 * z.x * z.y + c.y;
				z.x = z1.x;
			}
			color = (color > 10) ? (((color / 100) * 51) << 16) + (((color % 100) / 20 * 51) << 8) + (color % 20) / 4 * 51 : 0;
			ft_draw_pixel(d, p.x, p.y, color);
		}
}

void 	draw_juliaset(t_data *d)
{
	t_3d	c;
	t_2d	z;
	t_2d	z1;
	t_2d	p;
	int		color;

	p.y = -1;
	c.z = 0;
	while (++p.y <= YS && (p.x = -1))
		while (++p.x <= XS)
		{
			c.x = 3.5 * ((p.x - XS / 2) / d->zoom + XS / 2 - d->o1.x) / XS;
			c.y = 3.5 * ((p.y - YS / 2) / d->zoom + YS / 2 - d->o1.y) / YS;
			z.x = 0;
			z.y = 0;
			color = -1;
			while (++color < 500 && ABS(z.x * z.x - z.y * z.y) <= 4)
			{
				z1.x = (z.x * z.x - z.y * z.y) + c.x;
				z.y = 2 * z.x * z.y + c.y;
				z.x = z1.x;
			}
			color = (color > 10) ? (((color / 100) * 51) << 16) + (((color % 100) / 20 * 51) << 8) + (color % 20) / 4 * 51 : 0;
			ft_draw_pixel(d, p.x, p.y, color);
		}
}

int		ft_drawit(t_data *d)
{
	d->img_p = mlx_new_image(d->mlx, XS, YS);
	d->img_p0 = mlx_get_data_addr(d->img_p, &(d->bpp), &(d->ls), &(d->endian));
	draw_mandelset(d);
	mlx_clear_window(d->mlx, d->win);
	mlx_put_image_to_window(d->mlx, d->win, d->img_p, 0, 0);
	mlx_destroy_image(d->mlx, d->img_p);
	return (0);
}
