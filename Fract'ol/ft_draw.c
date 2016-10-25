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
#define	EPS 0.001

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

int		chk_roots(int param, t_2d z, t_2d zsqr)
{
	double temp1;
	double temp2;
	// int n_root;

	if (param / 10 == 3)
	{
		if ((zsqr.x - 2.0 * z.x + 1.0 + zsqr.y) <= EPS)
			return (1);
		if ((zsqr.x + z.x + zsqr.y + 1.0 - sqrt(3) * z.y) <= EPS)
			return (2);
		if ((zsqr.x + z.x + zsqr.y + 1.0 + sqrt(3) * z.y) <= EPS)
			return (3);
	}
	else if (param / 10 == 4)
	{
		z.y = z.y;
		temp2 = pow(z.x, 3);
		temp1 = temp2 * z.x;
		z.x = z.x - (temp1 * temp1 + 15 * temp1 - 16) / (8 * temp1 * temp2 + 60 * temp2);	
	}	
	else if (param / 10 == 5 && z.x != 0)
	{
		z.y = z.y;
		temp2 = pow(z.x, 3);
		temp1 = temp2 * z.x;
		z.x = z.x - (temp1 * temp1 + 15 * temp1 - 16) / (8 * temp1 * temp2 + 60 * temp2);
	}
	else if (param / 10 == 6)
	{
		temp1 = fmod(z.x, M_PI);
		temp2 = fmod(z.y, M_PI);
		if ((temp1 * temp1 + temp2 * temp2) <= EPS)
			return (z.x / M_PI + z.y / M_PI);
	}
	return (0);	
}

void	newton_iter(int param, t_2d *z, t_2d zsqr)
{
	double temp1;
	double temp2;

	if (param / 10 == 3 && zsqr.y + zsqr.x != 0)
	{
		z->y = z->y - (z->y + 2.0 * z->x * z->y / (zsqr.x + zsqr.y) / (zsqr.x + zsqr.y)) / 3.0;
		z->x = z->x - (z->x - (zsqr.x - zsqr.y) / (zsqr.x + zsqr.y) / (zsqr.x + zsqr.y)) / 3.0;	
	}
	if (param / 10 == 4)
	{
		z->y = z->y;
		temp2 = pow(z->x, 3);
		temp1 = temp2 * z->x;
		z->x = z->x - (temp1 * temp1 + 15 * temp1 - 16) / (8 * temp1 * temp2 + 60 * temp2);	
	}	
	if (param / 10 == 5 && z->x != 0)
	{
		z->y = z->y;
		temp2 = pow(z->x, 3);
		temp1 = temp2 * z->x;
		z->x = z->x - (temp1 * temp1 + 15 * temp1 - 16) / (8 * temp1 * temp2 + 60 * temp2);
	}
	if (param / 10 == 6)
	{
		// temp1 = z->y;
		temp2 = cos(z->x) * cos(z->x) * cosh(z->y) * cosh(z->y) + sin(z->x) * sin(z->x) * sinh(z->y) * sinh(z->y);
		if (temp2 != 0)
		{
			z->y = z->y - 0.5 * (/*cos(2 * z->x) * */sinh(2 * z->y) / temp2);
			z->x = z->x - 0.5 * (sin(2 * z->x) /** cosh(2 * temp1)*// temp2);
		}
	}
}

void 	draw_newtonset(t_data *d, int iter)
{
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
			zsqr.x = z.x * z.x;
			zsqr.y = z.y * z.y;
			while (++color < iter && !chk_roots(d->param, z, zsqr))
			{
				newton_iter(d->param, &z, zsqr);
				zsqr.x = z.x * z.x;
				zsqr.y = z.y * z.y;
			}
			if (d->param % 2 == 0)
			{
				ft_draw_pixel(d, p.x, p.y, HSVtoRGB(fmod((((float)chk_roots(d->param, z, zsqr) + d->cshift) / 1) * 6, 6),
				1, (fmod((((float)color + d->cshift) / 100) * 6, 1))));
				// ((zsqr.x - 2 * z.x + 1 + zsqr.y) <= EPS) ? ft_draw_pixel(d, p.x, p.y, (255 - color / iter) << 16) : 0;
				// ((zsqr.x + z.x + zsqr.y + 1 - sqrt(3) * z.y) <= EPS) ? ft_draw_pixel(d, p.x, p.y, (255 - color / iter) << 8) : 0;
				// ((zsqr.x + z.x + zsqr.y + 1.0 + sqrt(3) * z.y) <= EPS) ? ft_draw_pixel(d, p.x, p.y, 255 - color / iter) : 0;
			}
			else
				ft_draw_pixel(d, p.x, p.y, HSVtoRGB(fmod((((float)color + d->cshift) / 100) * 6, 6),
				1, (fmod((((float)color + d->cshift) / 100) * 6, 0.5) + 0.5)));
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
