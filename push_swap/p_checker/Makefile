# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:50:59 by mmoros            #+#    #+#              #
#    Updated: 2018/05/29 17:49:43 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ../checker

SRC =	checker.c		\
		node_stack.c	\
		node_ops.c		\
		ops1.c			\
		ops2.c			\
		ops3.c			

INC = checker.h

CC = gcc

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INC)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	@make -C ../ -C libft/
	@gcc $(CFLAGS) -c $(SRC) $(INC)
	@gcc -L../libft/ -lft $(OBJ) -o $(NAME)

clean:
	@/bin/rm -f $(OBJ) *.gch
	@make clean -C ../ -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C ../ -C libft/

re: fclean all
