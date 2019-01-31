# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoros <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/16 18:50:59 by mmoros            #+#    #+#              #
#    Updated: 2019/01/30 17:07:11 by mmoros           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -I $(LIBDIR) -I $(IDIR)

ODIR = .objects
SDIR = srcs
IDIR = inc
LIBDIR = libft/inc

FILES =	lem_in.c	\
		lem_input.c	\
		node_lem.c	\
		node_room.c

LIBS = libft/libft.a

OBJ = $(patsubst %.c, $(ODIR)/%.o, $(FILES))
SRC = $(patsubst %.c, $(SDIR)/%.c, $(FILES))

all: $(NAME)

$(NAME): $(LIBS) $(OBJ) $(ODIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -o $(NAME) $(SRC) $(LIBS) #HOW do i use obj instead of src?

$(ODIR)/%.o:
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

norm:
	@printf "%b" "$(LIB_COLOR)$(NAME): Checking Norm...\n$(NO_COLOR)"
	@norminette $(SRC) $(INCLUDES)
	@make -C libft norm
