example: src/example.c src/ppm.h
	gcc --static -o example src/example.c

run: example
	./example

default: example
