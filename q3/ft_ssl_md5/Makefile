# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:50:59 by mmoros            #+#    #+#              #
#    Updated: 2019/05/09 17:50:26 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -I $(LIBDIR) -I $(IDIR)

ODIR = .objects
SDIR = srcs
IDIR = inc
LIBDIR = libft/inc

FILES =	ft_ssl.c		\
		ft_md5.c		\
		ft_sha256.c		\
		read_input.c	\
		node_ssl.c		\
		node_512chunk.c

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
