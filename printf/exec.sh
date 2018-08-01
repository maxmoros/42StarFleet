make -C libft
make re
gcc testpf.c -L. -lftprintf *.o libft/*.o
