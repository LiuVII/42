/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 23:04:08 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/29 23:04:10 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

int			main(int argc, char **argv)
{
	int		size;
	int		tn;
	int		fd;
	t_tet	*tet_a;

	(argc != 2) ? write(1, "usage: ./fillit filename\n", 25) : 0;
	if (argc != 2)
		return (1);
	tet_a = NULL;
	tn = 0;
	if ((fd = open(argv[1], O_RDONLY)) > 0)
		tet_a = ft_read_file(fd, &tn);
	if ((fd > 0 && (close(fd) == -1 || !tet_a)) || fd <= 0)
	{
		if (!tet_a)
			write(1, "error\n", 6);
		else
			write(1, "usage: ./fillit filename\n", 25);
		return (1);
	}
	size = 1;
	while (size * size < 4 * tn)
		size++;
	ft_fill_main(size, tn, tet_a);
	return (0);
}
