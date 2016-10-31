/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 23:36:58 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/30 23:37:00 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		hsv_rgb(float hue, float sat, float val)
{
	float		rgb[3];
	float		x;
	float		c;

	c = sat * val;
	x = c * (1 - ABS(fmod(hue, 2) - 1));
	rgb[0] = (val * (1 - c) + c * (hue < 1 || hue >= 5)
		+ x * ((hue >= 1 && hue < 2) || (hue >= 4 && hue < 5))) * 255;
	rgb[1] = (val * (1 - c) + c * (hue >= 1 && hue < 3)
		+ x * ((hue >= 0 && hue < 1) || (hue >= 3 && hue < 4))) * 255;
	rgb[2] = (val * (1 - c) + c * (hue >= 3 && hue < 5)
		+ x * ((hue >= 2 && hue < 3) || (hue >= 5 && hue < 6))) * 255;
	return (((int)rgb[0] << 16) + ((int)rgb[1] << 8) + rgb[2]);
}

int		get_color(t_data *d, float z)
{
	int		s;
	int		e;
	float	hue;
	float	r;

	hue = fmod((ABS(d->clr) / 100.0) * 6.0, 6.0);
	s = d->cmin + hsv_rgb(hue, 1, (d->clr != 0));
	e = d->cmax + hsv_rgb(hue, 1, (d->clr != 0));
	if (d->cmean >= 0 && z >= d->zmean)
	{
		s = d->cmean + hsv_rgb(hue, 1, (d->clr != 0));
		r = (z - d->zmean) / (d->zmax - d->zmean);
	}
	else if (d->cmean >= 0 && z < d->zmean)
	{
		e = d->cmean + hsv_rgb(hue, 1, (d->clr != 0));
		r = (z - d->zmin) / (d->zmean - d->zmin);
	}
	else
		r = (z - d->zmin) / (d->zmax - d->zmin);
	z = (int)(((e >> 16) % 256 - (s >> 16) % 256) * r + (s >> 16) % 256) << 16;
	z += (int)(((e >> 8) % 256 - (s >> 8) % 256) * r + (s >> 8) % 256) << 8;
	z += (int)((e % 256 - s % 256) * r + s % 256);
	return (z);
}

int		set_color(t_3d p1, t_3d p2, t_3d p, int flag)
{
	float	ratio;

	ratio = 0;
	if (flag == 1)
		ratio = (p.x - p1.x) / (p2.x - p1.x);
	else if (flag == 2)
		ratio = (p.y - p1.y) / (p2.y - p1.y);
	p.z = (int)((((int)p2.z >> 16) % 256 - ((int)p1.z >> 16) % 256) * ratio
		+ ((int)p1.z >> 16) % 256) << 16;
	p.z += (int)((((int)p2.z >> 8) % 256 - ((int)p1.z >> 8) % 256) * ratio
		+ ((int)p1.z >> 8) % 256) << 8;
	p.z += (int)((((int)p2.z) % 256 - ((int)p1.z) % 256) * ratio
		+ ((int)p1.z) % 256);
	return (p.z);
}
