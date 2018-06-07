# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:50:59 by mmoros            #+#    #+#              #
#    Updated: 2018/05/02 22:23:37 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC =	lem-in.c

INC = lem-in.h

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
