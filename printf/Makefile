# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 15:34:53 by mmoros            #+#    #+#              #
#    Updated: 2018/04/30 00:16:30 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf

SRC =	ft_printf.c			\
		node_conv.c			\
		pf_parse.c			\
		pf_convf1.c			\
		pf_convf2.c			\
		pf_convf3.c			\
		pf_bigf1.c			\
		pf_bigf2.c			\
		libft/ft_memalloc.c	\
		libft/ft_strlen_c.c	\
		libft/ft_strncpy.c	\
		libft/ft_putstr.c	\
		libft/ft_putnbr.c	\
		libft/ft_puthex.c	\
		libft/ft_puthex_f.c	\
		libft/ft_isdigit.c	\
		libft/ft_isint.c	\
		libft/ft_atoi.c		\
		libft/ft_strncmp.c


INC = ft_printf.h
LIBFT = libft/libft.a
CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INC)
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(CFLAGS) -c $(SRC)
	@ar rcs libftprintf.a $(OBJ)
	@ranlib libftprintf.a

clean:
	@/bin/rm -f $(OBJ) *.gch
	@rm *.o
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
