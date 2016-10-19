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

void	ft_free_n_exit(t_data *data)
{
	int i;
	int j;

	mlx_destroy_window(data->mlx, data->win);
	i = -1;
	while (++i < data->img_size.z && (j = -1))
	{
		while (++j < data->img_size.y)
			free(data->image[i][j]);
		free(data->image[i]);
	}
	free(data->image);
	(data->mlx) ? free(data->mlx) : 0;
	exit(0);
}

int	ft_key_hook(int keycode, t_data *data)
{
	(keycode == KEY_ESC) ? ft_free_n_exit(data) : 0;
	(keycode == KEY_UP) ? data->O1.y += 10 : 0;
	(keycode == KEY_DOWN) ?	data->O1.y -= 10 : 0;
	(keycode == KEY_LEFT) ?	data->O1.x += 10 : 0;
	(keycode == KEY_RIGHT) ? data->O1.x -= 10 : 0;
	(keycode == KEY_4) ? data->phi += 0.05 : 0;
	(keycode == KEY_1) ? data->phi -= 0.05 : 0;
	(keycode == KEY_5) ? data->teta -= 0.05 : 0;
	(keycode == KEY_2) ? data->teta += 0.05 : 0;
	(keycode == KEY_PLUS) ? data->zoom *= 1.2 : 0;
	(keycode == KEY_MINUS) ? data->zoom /= 1.2 : 0;
	if (keycode == KEY_E)
	{
		data->phi = 0;
		data->teta= 0;
	}
	if (keycode == KEY_I)
	{
		data->phi = M_PI * (35.264 / 180);
		data->teta= M_PI / 4 ;
	}
	ft_drawit(data);
	//ft_putnbr(keycode);
	return (0);
}

int	ft_mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 1 || button == 2)
	{
		data->O1.x += (XS / 2 - x) / data->zoom;
		data->O1.y += (YS / 2 - y) / data->zoom;
	}
	if (button == 5)
		data->zoom *= 1.2;
	else if (button == 4)
		data->zoom /= 1.2;
	ft_drawit(data);
	return (0);
}
