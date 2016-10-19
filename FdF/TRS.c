/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TRS.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 21:51:48 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 21:51:50 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	ft_translate(t_3d p, t_3d tr)
{
	t_3d np;

	np.x = p.x + tr.x;
	np.y = p.y + tr.y;
	np.z = p.z;
	return (np);
}

t_3d	ft_rotate(t_3d p, float phi, float teta)
{
	t_3d np;

	np.x = cos(teta) * p.x - sin(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	np.y = cos(phi) * p.y - sin (phi) * p.z;
	np.z = sin(teta) * p.x + cos(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	return (np);
}

t_3d	ft_zoom(t_3d p, float zoom, t_2d Oz)
{
	t_3d np;

	np.x = XS / 2 + (p.x - Oz.x) * zoom;
	np.y = YS / 2 + (p.y - Oz.y) * zoom;
	np.z = p.z;
	return (np);
}

t_3d	ft_scale(t_3d p, t_3d scale)
{
	t_3d np;

	np.x = p.x * scale.x;
	np.y = p.y * scale.y;
	np.z = p.z * scale.z;
	return (np);
}

t_3d	p_trans(t_data *data, t_3d p)
{
	t_3d	np;

	np = ft_zoom(ft_translate(ft_rotate(ft_scale(p, data->scale),
		data->phi, data->teta), data->O1), data->zoom, data->Oz);
	np.z = get_color(data->zmin, data->zmax, data->zmean, p.z);
	return (np);
}