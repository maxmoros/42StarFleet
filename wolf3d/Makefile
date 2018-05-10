# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:50:59 by mmoros            #+#    #+#              #
#    Updated: 2018/05/09 20:08:34 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC =	wolf3d.c		\
		wolf_geng.c		\
		node_map.c		\
		node_plr.c		\
		node_ray.c		\
		node_io.c		\
		node_wolf_inst.c

INC = 	wolf3d.h				\
		minilibx_macos/mlx.h

CC = gcc

MLX = minilibx_macos/libmlx.a -framework OpenGL -framework  Appkit

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INC)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(CFLAGS) -c $(SRC) $(INC)
	@gcc -Llibft/ -lft $(OBJ) -o $(NAME) $(MLX)

clean:
	@/bin/rm -f $(OBJ) *.gch
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
