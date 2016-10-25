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

int		HSVtoRGB(float hue, float sat, float val)
{
	float		rgb[3];
	float		x;
	float		c;

	c = sat * val;
	x = c * (1 - ABS(fmod(hue, 2) - 1));
	rgb[0] = (val * (1 - c) + c * (hue < 1 || hue >= 5) + x * ((hue >= 1 && hue < 2) || (hue >= 4 && hue < 5))) * 255;
	rgb[1] = (val * (1 - c) + c * (hue >= 1 && hue < 3) + x * ((hue >= 0 && hue < 1) || (hue >= 3 && hue < 4))) * 255;
	rgb[2] = (val * (1 - c) + c * (hue >= 3 && hue < 5) + x * ((hue >= 2 && hue < 3) || (hue >= 5 && hue < 6))) * 255;
	return (((int)rgb[0]  << 16) + ((int)rgb[1] << 8) + rgb[2]);
}

int		get_color(double zmin, double zmax, double zmean, double z)
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

void 	draw_mandelset(t_data *d, int iter)
{
	t_2d	c;
	t_2d	z;
	t_2d	zsqr;
	t_2d	p;
	int		color;

	p.y = -1;
	while (++p.y <= YS && (p.x = -1))
		while (++p.x <= XS && (color = -1))
		{
			c.x = 3.5 * (p.x / d->zoom - d->o1.x) / XS;
			c.y = 3.5 * (p.y / d->zoom - d->o1.y) / YS;
			z.x = 0;
			z.y = 0;
			zsqr.x = 0;
			zsqr.y = 0;
			while (++color < iter && zsqr.x + (zsqr.y = z.y * z.y) <= 4)
			{
				z.y = (z.y + z.x) * (z.y + z.x) - zsqr.x - zsqr.y + c.y;
				z.x = zsqr.x - zsqr.y + c.x;
				zsqr.x = z.x * z.x;
			}
			ft_draw_pixel(d, p.x, p.y, HSVtoRGB(fmod((((float)color + d->cshift) / 200) * 6, 6),
				(fmod((((float)color + d->cshift) / 400) * 6, 0.5) + 0.5), 1 * (color < iter)));
		}
}

void 	draw_juliaset(t_data *d, int iter)
{
	t_3d	c;
	t_2d	z;
	t_2d	zsqr;
	t_2d	p;
	int		color;

	p.y = -1;
	while (++p.y <= YS && (p.x = -1))
		while (++p.x <= XS && (color = -1))
		{
			z.x = 3.5 * (p.x / d->zoom - d->o1.x) / XS;
			z.y = 3.5 * (p.y / d->zoom - d->o1.y) / YS;
			c.x = 3.5 * (d->oz.x - XS / 2) / XS;
			c.y = 3.5 * (d->oz.y - YS / 2) / YS;
			zsqr.x = z.x * z.x;
			zsqr.y = z.y * z.y;
			while (++color < iter && zsqr.x + (zsqr.y = z.y * z.y) <= 4)
			{
				z.y = (z.y + z.x) * (z.y + z.x) - zsqr.x - zsqr.y + c.y;
				z.x = zsqr.x - zsqr.y + c.x;
				zsqr.x = z.x * z.x;
			}
			ft_draw_pixel(d, p.x, p.y, HSVtoRGB(fmod((((float)color + d->cshift) / 200) * 6, 6),
				1, (fmod((((float)color + d->cshift) / 400) * 6, 0.5) + 0.5) * (color < iter)));
		}
}

void 	draw_newtonset(t_data *d, int iter)
{
	t_3d	c;
	t_2d	z;
	t_2d	p;
	t_2d	zsqr;
	int		color;

	p.y = -1;
	while (++p.y <= YS && (p.x = -1))
		while (++p.x <= XS && (color = -1))
		{
			z.x = 3.5 * (p.x / d->zoom - d->o1.x) / XS;
			z.y = 3.5 * (p.y / d->zoom - d->o1.y) / YS;
			c.x = -1;
			c.y = 0;
			zsqr.x = z.x * z.x;
			zsqr.y = z.y * z.y;
			while (++color < iter && zsqr.y + zsqr.x != 0 && (zsqr.x - 2.0 * z.x + 1.0 + zsqr.y) > 0.01 &&
				(zsqr.x + z.x + zsqr.y + 1.0 - sqrt(3) * z.y) > 0.01 && (zsqr.x + z.x + zsqr.y + 1.0 + sqrt(3) * z.y) > 0.01)
			{
				z.y = z.y - (z.y + 2.0 * z.x * z.y / (zsqr.x + zsqr.y) / (zsqr.x + zsqr.y)) / 3.0;
				z.x = z.x - (z.x - (zsqr.x - zsqr.y) / (zsqr.x + zsqr.y) / (zsqr.x + zsqr.y)) / 3.0;
				zsqr.x = z.x * z.x;
				zsqr.y = z.y * z.y;
			}
			color = iter - color;
			if ((zsqr.x - 2.0 * z.x + 1.0 + zsqr.y) <= 0.01)
				ft_draw_pixel(d, p.x, p.y, 0x00FF0000);
			else if ((zsqr.x + z.x + zsqr.y + 1.0 - sqrt(3) * z.y) <= 0.01)
				ft_draw_pixel(d, p.x, p.y, 0x0000FF00);
			else if ((zsqr.x + z.x + zsqr.y + 1.0 + sqrt(3) * z.y) <= 0.01)
				ft_draw_pixel(d, p.x, p.y, 0x000000FF);
			// ft_draw_pixel(d, p.x, p.y, HSVtoRGB(fmod((((float)color + d->cshift) / 200) * 6, 6),
			// 	1, (fmod((((float)color + d->cshift) / 400) * 6, 0.5) + 0.5) * (color != 0)));
		}
}

int		ft_drawit(t_data *d)
{
	d->img_p = mlx_new_image(d->mlx, XS, YS);
	d->img_p0 = mlx_get_data_addr(d->img_p, &(d->bpp), &(d->ls), &(d->endian));
	if (d->param == 1)
		draw_mandelset(d, d->iter);
	else if (d->param == 2)
		draw_juliaset(d, d->iter);
	else
		draw_newtonset(d, d->iter / 2);
	mlx_clear_window(d->mlx, d->win);
	mlx_put_image_to_window(d->mlx, d->win, d->img_p, 0, 0);
	mlx_destroy_image(d->mlx, d->img_p);
	return (0);
}
