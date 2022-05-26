all:
	mkdir -p bin
	gcc src/*.c -I include -o bin/bmpinfo -Wall -Wextra
