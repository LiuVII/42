/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:48:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/10/13 14:48:18 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	ft_displayit(t_data *d)
{
// 	ft_putstr("\
// ____________________________\n\
// CONTROLS:\n\
// Translation:\n\
// 	Y: Key: UP, DOWN\n\
// 	X: Key: LEFT, RIGHT\n\n\
// Rotation:\n\
// 	X: Numpad: 1, 4\n\
// 	Y: Numpad: 2, 5\n\n\
// Zoom:\n\
// 	IN: Numpad: + | Mouse scroll\n\
// 	OUT: Numpad: -| Mouse scroll\n\n\
// Projections:\n\
// 	Elevation (init): E\n\
// 	Isometric: Key: I\n\n\
// Center:\n\
// 	Mouse click: Btn 1, Btn 2\n\
// ____________________________\n\
// 	");
	mlx_expose_hook(d->win, ft_drawit, d);
	mlx_mouse_hook(d->win, ft_mouse_hook, d);
	mlx_key_hook(d->win, ft_key_hook, d);
	mlx_loop(d->mlx);
}

void	ft_puterr_msg(int err)
{
	if (err == -1)
		ft_putendl("usage: .fractol/ $(param)");
	else if (err == -2)
		ft_putendl("error: mlx initializing failed");
	else if (err == -3)
		ft_putendl("error: window initializing failed");
	else if (err == -4)
		ft_putendl("error: while opening/reading a file");
	else if (err == -5)
		ft_putendl("error: memory allocation");
	else if (err == -10)
		ft_putendl("error: invalid map");
	else
		ft_putendl("error: unknown");
}

void	ft_free_n_exit(t_data *d, int err)
{
	(d && d->mlx && d->win) ? mlx_destroy_window(d->mlx, d->win) : 0;
	(d && d->mlx) ? free(d->mlx) : 0;
	(d) ? free(d) : 0;
	(err < 0) ? ft_puterr_msg(err) : 0;
	(err >= 0) ? exit(0) : exit(1);
}

void	data_init(t_data *d)
{
	d->o1.x = XS * 1 / 2;
	d->o1.y = YS / 2;
	d->oz.x = XS / 2;
	d->oz.y = YS / 2;
	d->zoom = 1;
	d->phi = 0;
	d->teta = 0;
	d->scale.x = 25;
	d->scale.y = 25;
	d->scale.z = 25;
	d->iter = 84;
	d->cshift = 0;
}

int		main(int argc, char **argv)
{
	t_data *d;

	if (!(argc > 1 && argv[1]))
	{
		ft_puterr_msg(-1);
		return (1);
	}
	if (!(d = (t_data*)malloc(sizeof(t_data))))
	{
		ft_puterr_msg(-5);
		return (1);
	}
	data_init(d);
	d->param = ft_atoi(argv[1]);
	if (!(d->mlx = mlx_init()))
		ft_free_n_exit(d, -2);
	if (!(d->win = mlx_new_window(d->mlx, XS, YS, argv[1])))
		ft_free_n_exit(d, -3);
	ft_displayit(d);
	return (0);
}
