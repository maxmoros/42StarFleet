all: bin server client gfx

server:
	make -C server

client:
	make -C client

gfx:
	make -C gfx

bin:
	mkdir -p bin/

clean:
	make -C server clean

fclean: clean
	rm -rf bin
	make -C server fclean

test:
	make -C server test

re: fclean all

.PHONY: clean fclean all re server client gfx
