NAME = libfts.a
CFLAGS = -f 
LFLAGS = ar rc
CC = nasm

ODIR = .objects
SDIR = srcs
IDIR = inc

SRC =	\
		ft_abs.s		\
		ft_bzero.s		\
		ft_strcat.s		\
		ft_isalpha.s	\
		ft_isdigit.s	\
		ft_isalnum.s	\
		ft_isalnum.s	\
		ft_isascii.s	\
		ft_islower.s	\
		ft_isprint.s	\
		ft_isspace.s	\
		ft_isupper.s	\
		ft_math_swap.s	\
		ft_toupper.s	\
		ft_tolower.s	\
		ft_puts.s		\
		ft_strlen.s		\
		ft_memset.s		\
		ft_memcpy.s		\
		ft_strdup.s		\
		ft_cat.s

OBJS = $(patsubst %.s, $(ODIR)/%.o, $(SRC))

PREFIX =

ifeq ($(shell uname -s), Darwin)
		CFLAGS += macho64
		PREFIX = --prefix _ -dOSX=1
else
		echo "Built for OSX system. Closing Makefile..."
endif

all: $(NAME)

$(NAME): $(ODIR) $(OBJS)
		$(LFLAGS) $(NAME) $(OBJS)

$(ODIR)/%.o: $(addprefix $(SDIR)/, %.s)
		$(CC) $(CFLAGS) -o $@ $(PREFIX) $^
	
$(ODIR):
		mkdir -p $(ODIR)

test:
		cd max_tests && $(MAKE) && cd ..

.phony: clean re fclean

fclean: clean
		rm -rf $(NAME)

clean:
		rm -rf $(OBJS) testy
		rm -rf $(ODIR)
		cd max_tests && $(MAKE) clean && cd ..

re: fclean all

