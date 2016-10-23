/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:27:50 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/23 15:27:52 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <math.h>

# define XS 600
# define YS 600
# define ZS 100
# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_4 86
# define KEY_1 83
# define KEY_5 87
# define KEY_2 84
# define KEY_7 89
# define KEY_8 91
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_E 14
# define KEY_I 34
# define SIGN(x) ((x < 0.0) ? -1.0 : 1.0)
# define ABS(x) ((x) * SIGN(x))

typedef struct	s_2d
{
	double		x;
	double		y;
}				t_2d;

typedef struct	s_3d
{
	double		x;
	double		y;
	double		z;
}				t_3d;

typedef struct	s_data
{
	int			iter;
	void		*mlx;
	void		*win;
	void		*img_p;
	char		*img_p0;
	t_3d		o1;
	double		phi;
	double		teta;
	double		zoom;
	t_3d		scale;
	t_2d		oz;
	int			param;
	int			bpp;
	int			ls;
	int			cshift;
	int			endian;
}				t_data;

int				ft_key_hook(int keycode, t_data *d);
int				ft_mouse_hook(int button, int x, int y, t_data *d);
int				ft_read(char *filename, t_data *d);
void			ft_free_n_exit(t_data *d, int err);
int				ft_drawit(t_data *d);
t_3d			ft_tr(t_data *d, t_3d p);
int				get_color(double zmin, double zmax, double zmean, double z);

#endif
