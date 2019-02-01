NAME = main

CC = gcc
CFLAGS += -Wall -Wextra -Wno-unused-function -pedantic -o $(NAME) -I../inc -g
LDFLAGS += -L..
LDLIBS += -lfts

ODIR = .objects

OBJ = $(NAME).o \
		libft.o \
		ck_bonus.o \
		ck_bzero.o \
		ck_cat.o \
		ck_isto.o \
		ck_memcpy.o \
		ck_memset.o \
		ck_puts.o \
		ck_strcat.o \
		ck_strdup.o \
		ck_strlen.o 

all: $(NAME)

$(NAME): $(OBJ) ../libfts.a

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
