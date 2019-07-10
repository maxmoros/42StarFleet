# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <mmoros@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:50:59 by mmoros            #+#    #+#              #
#    Updated: 2019/07/09 18:57:34 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I $(LIBDIR) -I $(IDIR)

ODIR = .objects
SDIR = srcs
IDIR = inc
LIBDIR = libft/inc

FILES =	ls.c			\
		ls_print.c		\
		ls_print_l.c	\
		ls_misc.c		\
		node_dir.c

LIBS = libft/libft.a

VPATH = srcs

OBJ = $(patsubst %.c, $(ODIR)/%.o, $(FILES))
SRC = $(patsubst %.c, $(SDIR)/%.c, $(FILES))

all: $(NAME)

$(NAME): $(LIBS) $(OBJ) $(ODIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -o $(NAME) $(SRC) $(LIBS)

$(ODIR)/%.o: $(ODIR) %.c
	$(CC) $(CFLAGS) -o $@ $(SRC) $(INC_FLAGS) $(LIBS)

$(ODIR):
	mkdir -p $(ODIR)

$(LIBS): libft
	@make -C libft/

.PHONY: clean re fclean

clean:
	@/bin/rm -f $(OBJ) *.gch
	@make clean -C libft/

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C libft/

re: fclean all
