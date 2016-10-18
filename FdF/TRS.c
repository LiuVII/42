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

	// p.x = p.x - XS / 2;
	// p.y = YS / 2 - p.y;
	np.x = cos(teta) * p.x - sin(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	np.y = cos(phi) * p.y - sin (phi) * p.z;
	np.z = sin(teta) * p.x + cos(teta) * (sin(phi) * p.y + cos (phi) * p.z);
	// np.x = np.x + XS / 2;
	// np.y = YS / 2 - np.y;
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
