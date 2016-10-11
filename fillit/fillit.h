/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 17:18:31 by mfilipch          #+#    #+#             */
/*   Updated: 2016/09/28 17:20:13 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef char				t_tet[4][4];
typedef unsigned long long	t_bit_map[4];
typedef unsigned long long	t_ull;

void			ft_mapprint(char **map);
void			ft_mapfree(char ***map);
void			ft_postomap(char *pos, int size, t_tet *tet_a);
t_tet			*ft_read_file(int fd, int *tn);
char			**ft_mapmake(int rows, int cols, char c);
int				ft_fill_main(int size, int num, t_tet *tet_a);
void			ft_bit_rev_print(void *addr, size_t size);
void			ft_tet_to_bit(t_ull *ll, t_tet tet);
void			ft_map_to_bit(t_ull *ll, char **map, int size);
void			ft_map_reset(t_ull *tmp, t_ull *lmap, int r, int c);
t_ull			ft_get_start_bits(unsigned char size);
void			ft_create_bitmap(unsigned char size, t_bit_map *map);
void			ft_solcompare(char *str1, char *str2, int tnum, int *sol);

#endif
