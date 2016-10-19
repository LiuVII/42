/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:27:50 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/23 15:27:52 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <math.h>

# define XS 1200
# define YS 800
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
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_E 14
# define KEY_I 34
# define SIGN(x) ((x < 0.0) ? -1.0 : 1.0)
# define ABS(x) ((x) * SIGN(x))

typedef struct	s_2d
{
	float	x;
	float	y;
}				t_2d;

typedef struct	s_3d
{
	float	x;
	float	y;
	float	z;
}				t_3d;

typedef struct	s_data
{
	t_3d		***image;
	t_3d		img_size;
	void		*mlx;
	void		*win;
	void		*img;
	char		*img0;
	t_3d		O1;
	float		phi;
	float		teta;
	float		zoom;
	t_3d		scale;
	t_2d		Oz;
	float		zmin;
	float		zmax;
	float		zmean;
	int			bpp;
	int			ls;
	int			endian;
}				t_data;

int		ft_key_hook(int keycode, t_data *data);
int		ft_mouse_hook(int button, int x, int y, t_data *data);
int		ft_read(char *filename, t_data *data);
// void	ft_set_image(t_data *data);
void	ft_drawit(t_data *data);
t_3d	p_trans(t_data *data, t_3d p);
int		get_color(float zmin, float zmax, float zmean, float z);

#endif
