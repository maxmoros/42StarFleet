# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 15:34:53 by mmoros            #+#    #+#              #
#    Updated: 2018/07/31 19:09:23 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC =	ft_printf.c			\
		node_conv.c			\
		pf_parse.c			\
		pf_convf1.c			\
		pf_convf2.c			\
		pf_convf3.c			\
		pf_bigf1.c			\
		pf_bigf2.c			\
		libft/ft_memalloc.c	\
		libft/ft_math_abs.c	\
		libft/ft_strlen_c.c	\
		libft/ft_strlen.c	\
		libft/ft_strncpy.c	\
		libft/ft_putstr.c	\
		libft/ft_putchar.c	\
		libft/ft_putnbr.c	\
		libft/ft_puthex.c	\
		libft/ft_puthex_f.c	\
		libft/ft_isdigit.c	\
		libft/ft_isint.c	\
		libft/ft_atoi.c		\
		libft/ft_strncmp.c


INC = ft_printf.h
CC = gcc
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ)
	@/bin/rm -f $(NAME)
	@ar rcs $(NAME) $(OBJ)
	@ranlib libftprintf.a

clean:
	@/bin/rm -f $(OBJ)
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: clean all
