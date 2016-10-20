# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfilipch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/22 09:34:02 by mfilipch          #+#    #+#              #
#    Updated: 2016/10/09 23:56:07 by mfilipch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

FUNCS		+=	main.c\
				hooks.c\
				ft_trs.c\
				ft_draw.c\
				ft_read.c

LIBFT		=	./libft/libft.a
LIBINC		=	-I./libft
LIBLINK		=	-L./libft -lft

MLX			=	./minilibx/libmlx.a
MLXINC		=	-I./minilibx
MLXLINK		=	-L./minilibx -lmlx -framework OpenGL -framework AppKit

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
OBJS		=	$(addprefix $(OBJS_DIR), $(FUNCS:.c=.o))

INC_DIR		=	./includes/
OBJS_DIR	=	./build/

.PHONY: all clean fclean re

all: $(LIBFT) $(MLX) $(NAME)

build:
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: %.c | build
	@$(CC) $(CFLAGS) $(LIBINC) $(MLXINC) -I $(INC_DIR) -c $< -o $@

$(LIBFT):
	@make -C ./libft

$(MLX):
	@make -C ./minilibx

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(MLXLINK) $(LIBLINK)

clean:
	@/bin/rm -rf $(OBJS_DIR)
	@make -C ./libft clean
	@make -C ./minilibx clean
	@/bin/rm -f *.out
	@/bin/rm -f ._*
	@/bin/rm -f .DS*

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
