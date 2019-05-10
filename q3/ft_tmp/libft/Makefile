# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 15:34:53 by mmoros            #+#    #+#              #
#    Updated: 2019/02/02 18:47:58 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(IDIR)

ODIR = .objects
SDIR = srcs
IDIR = inc

FILES =	ft_atoi.c			\
		ft_bzero.c			\
		ft_isalnum.c		\
		ft_isalldig.c		\
		ft_isalpha.c		\
		ft_isascii.c		\
		ft_isdigit.c		\
		ft_isint.c			\
		ft_isprint.c		\
		ft_itoa.c			\
		ft_lstadd.c			\
		ft_lstdel.c			\
		ft_lstdelone.c		\
		ft_lstiter.c		\
		ft_lstmap.c			\
		ft_lstnew.c			\
		ft_math_abs.c		\
		ft_math_gcd.c		\
		ft_math_isprime.c	\
		ft_math_pow.c		\
		ft_math_sqrt_t.c	\
		ft_math_sqrt_f.c	\
		ft_math_swap.c		\
		ft_median.c			\
		ft_memalloc.c		\
		ft_memccpy.c		\
		ft_memchr.c			\
		ft_memcmp.c			\
		ft_memcpy.c			\
		ft_memdel.c			\
		ft_memmove.c		\
		ft_memset.c			\
		ft_putchar.c		\
		ft_putchar_fd.c		\
		ft_putendl.c		\
		ft_putendl_fd.c		\
		ft_putoct.c			\
		ft_puthex.c			\
		ft_puthex_f.c		\
		ft_putnbr.c			\
		ft_putunbr.c		\
		ft_putnbr_fd.c		\
		ft_putstr.c			\
		ft_putnstr.c		\
		ft_putstr_fd.c		\
		ft_qsort.c			\
		ft_strcat.c			\
		ft_strchr.c			\
		ft_strclr.c			\
		ft_strcmp.c			\
		ft_strcpy.c			\
		ft_strdel.c			\
		ft_strdup.c			\
		ft_strequ.c			\
		ft_striter.c		\
		ft_striteri.c		\
		ft_strjoin.c		\
		ft_strlcat.c		\
		ft_strlen.c			\
		ft_strlen_c.c		\
		ft_strmap.c			\
		ft_strmapi.c		\
		ft_strncat.c		\
		ft_strncmp.c		\
		ft_strncpy.c		\
		ft_strndup.c		\
		ft_strnequ.c		\
		ft_strnew.c			\
		ft_strnstr.c		\
		ft_strrchr.c		\
		ft_strsplit.c		\
		ft_strstr.c			\
		ft_strsub.c			\
		ft_strtrim.c		\
		ft_tolower.c		\
		ft_toupper.c		\
		ft_wordchomp_d.c	\
		ft_wordcount_d.c	\
		get_next_line.c


OBJ = $(patsubst %.c, $(ODIR)/%.o, $(FILES))
SRC = $(patsubst %.c, $(SDIR)/%.c, $(FILES))

VPATH = $(SDIR)

all: $(NAME)

$(NAME): $(OBJ) 
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

$(ODIR)/%.o: %.c $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR):
	mkdir -p $(ODIR)

.PHONY: clean re fclean

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
