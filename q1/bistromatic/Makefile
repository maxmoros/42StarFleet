# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 15:34:53 by mmoros            #+#    #+#              #
#    Updated: 2018/04/26 20:28:58 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = calc

SRC =	bistro.c		\
		node_num.c		\
		node_equ.c		\
		parse_equ.c	

INC = bistro.h
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
	@rm *.o *.gch

clean:
	@/bin/rm -f $(OBJ) *.gch
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
