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

int	ft_close(t_data *d)
{
	ft_free_n_exit(d, NULL, NULL, 0);
	return (0);
}

int	ft_key_hook(int keycode, t_data *d)
{
	(keycode == KEY_ESC) ? ft_free_n_exit(d, NULL, NULL, 0) : 0;
	(keycode == KEY_UP) ? d->o1.y -= 10 : 0;
	(keycode == KEY_DOWN) ? d->o1.y += 10 : 0;
	(keycode == KEY_LEFT) ? d->o1.x -= 10 : 0;
	(keycode == KEY_RIGHT) ? d->o1.x += 10 : 0;
	(keycode == KEY_4) ? d->phi += 0.05 : 0;
	(keycode == KEY_1) ? d->phi -= 0.05 : 0;
	(keycode == KEY_5) ? d->teta -= 0.05 : 0;
	(keycode == KEY_2) ? d->teta += 0.05 : 0;
	(keycode == KEY_6) ? d->psi -= 0.05 : 0;
	(keycode == KEY_3) ? d->psi += 0.05 : 0;
	(keycode == KEY_7) ? d->clr += 5 : 0;
	(keycode == KEY_8) ? d->clr -= 5 : 0;
	(keycode == KEY_E) ? d->phi = 0 : 0;
	(keycode == KEY_E) ? d->teta = 0 : 0;
	(keycode == KEY_E) ? d->psi = 0 : 0;
	(keycode == KEY_I) ? d->phi = M_PI / 4 : 0;
	(keycode == KEY_I) ? d->teta = -M_PI / 6 : 0;
	(keycode == KEY_I) ? d->psi = -M_PI / 6 : 0;
	ft_drawit(d);
	return (0);
}

int	ft_mouse_down(int button, int x, int y, t_data *d)
{
	if (x >= 0 && x <= XS && y >= 0 && YS <= YS)
	{
		d->mevent = button;
		(button == 1) ? d->oz.x = x : 0;
		(button == 1) ? d->oz.y = y : 0;
	}
	if (button == 2)
	{
		d->o1.x += (XS / 2 - x) / d->zoom;
		d->o1.y += (YS / 2 - y) / d->zoom;
	}
	if (button == 5 && d->zoom <= 10000)
	{
		d->o1.x -= x / d->zoom * (1 - 1 / 1.2);
		d->o1.y -= y / d->zoom * (1 - 1 / 1.2);
		d->zoom *= 1.2;
	}
	else if (button == 4 && d->zoom >= 0.001)
	{
		d->o1.x -= x / d->zoom * (1 - 1.2);
		d->o1.y -= y / d->zoom * (1 - 1.2);
		d->zoom /= 1.2;
	}
	ft_drawit(d);
	return (0);
}

int	ft_mouse_up(int button, int x, int y, t_data *d)
{
	if (button)
		d->mevent = 0 * (x - y);
	return (0);
}

int	ft_mouse_drag(int x, int y, t_data *d)
{
	if (d->mevent == 1 && x >= 0 && x <= XS && y >= 0 && y <= YS)
	{
		d->o1.x += (x - d->oz.x) / d->zoom;
		d->o1.y += (y - d->oz.y) / d->zoom;
		d->oz.x = x;
		d->oz.y = y;
		ft_drawit(d);
	}
	return (0);
}
