# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/22 09:34:02 by mfilipch          #+#    #+#              #
#    Updated: 2016/09/22 09:34:04 by mfilipch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fillit

FILE_NAME	=	ft_bit_fillit_opt.c\
				main.c

LIB_NAME	=	libft.a

LIB_FUNCS	+=	ft_atoi.c\
				ft_memset.c\
				ft_map.c\
				ft_read.c\
				ft_putendl.c\
				ft_bit_map.c

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
LIB_OBJS	=	$(addprefix build/, $(LIB_FUNCS:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB_NAME)
	@$(CC) $(CFLAGS) -o $(NAME) $(FILE_NAME) -L. $(LIB_NAME)

$(LIB_NAME): $(LIB_OBJS)
	@ar rcs $@ $^

build:
	@mkdir build

build/%.o: %.c libft.h | build
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@/bin/rm -rf build/

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f *.out
	@/bin/rm -f $(LIB_NAME)

re: fclean all
