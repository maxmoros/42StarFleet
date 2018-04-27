# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 15:34:53 by mmoros            #+#    #+#              #
#    Updated: 2018/04/16 19:08:09 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = grimly

SRC =	grimly.c		\
		grim_init.c		\
		grim_solve.c	\
		grim_adv1.c		\
		grim_adv2.c		\
		grim_adv3.c		\
		grim_actor.c

INC = grimly.h
CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INC)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(CFLAGS) -c $(SRC) $(INC)
	@gcc -Llibft/ -lft $(OBJ) -o $(NAME)

clean:
	@/bin/rm -f $(OBJ) *.gch
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
