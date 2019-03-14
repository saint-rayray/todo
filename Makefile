CFLAGS=-Wall -g -Wextra -pedantic

all:
	rm -f todo
	make todo
	clear
	./todo
