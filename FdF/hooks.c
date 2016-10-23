/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 22:00:05 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/15 22:00:06 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_key_hook(int keycode, t_data *d)
{
	(keycode == KEY_ESC) ? ft_free_n_exit(d, NULL, NULL, 0) : 0;
	(keycode == KEY_UP) ? d->o1.y += 10 : 0;
	(keycode == KEY_DOWN) ? d->o1.y -= 10 : 0;
	(keycode == KEY_LEFT) ? d->o1.x += 10 : 0;
	(keycode == KEY_RIGHT) ? d->o1.x -= 10 : 0;
	(keycode == KEY_4) ? d->phi += 0.05 : 0;
	(keycode == KEY_1) ? d->phi -= 0.05 : 0;
	(keycode == KEY_5) ? d->teta -= 0.05 : 0;
	(keycode == KEY_2) ? d->teta += 0.05 : 0;
	(keycode == KEY_PLUS) ? d->zoom *= 1.2 : 0;
	(keycode == KEY_MINUS) ? d->zoom /= 1.2 : 0;
	if (keycode == KEY_E)
	{
		d->phi = 0;
		d->teta = 0;
	}
	if (keycode == KEY_I)
	{
		d->phi = M_PI * (35.264 / 180);
		d->teta = M_PI / 4;
	}
	ft_drawit(d);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_data *d)
{
	if (button == 2)
	{
		d->o1.x += (XS / 2 - x) / d->zoom;
		d->o1.y += (YS / 2 - y) / d->zoom;
	}
	if (button == 5)
	{
		d->o1.x -= x / d->zoom * (1 - 1 / 1.2);
		d->o1.y -= y / d->zoom * (1 - 1 / 1.2);	
		d->zoom *= 1.2;
	}
	else if (button == 4)
	{
		d->o1.x -= x / d->zoom * (1 - 1.2);
		d->o1.y -= y / d->zoom * (1 - 1.2);
		d->zoom /= 1.2;
	}
	ft_drawit(d);
	return (0);
}
