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

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define SIGN(x) ((x < 0.0) ? -1.0 : 1.0)
# define ABS(x) (x * SIGN(x))

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

typedef struct	s_vertex
{
	t_3d	*thumb;
	t_3d	*index;
	t_3d	*middle;
}				t_vertex;

typedef struct	s_data
{
//	t_vertex	***image;
	t_3d		***image;
	t_3d		img_size;
	void		*mlx;
	void		*win;
	t_3d		O1;
	float		phi;
	float		teta;
	t_3d		zoom;
	t_2d		Oz;
//	t_vertex	*xyz1;
}				t_data;

#endif
