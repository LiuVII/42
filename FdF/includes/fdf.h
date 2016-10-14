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
# include <math.h>

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

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
	t_vertex	***image;
	void		*mlx;
	void		*win;
	t_3d		*O1;
	float		phi;
	float		teta;
	t_vertex	*xyz1;
}				t_data;

#endif
