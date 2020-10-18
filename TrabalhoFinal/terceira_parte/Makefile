all: clean init go

init: library
	gcc main.c -o main libTiny.a 

library: list tiny
	ar rcs libTiny.a list.o alloc.o asmCode.o errors.o input.o output.o parser.o scanner.o


list: list.c list.h
	gcc -c list.c 

tiny: alloc.c alloc.h asmCode.c asmCode.h errors.c errors.h input.c input.h output.c output.h parser.c parser.h scanner.c scanner.h
	gcc -c alloc.c asmCode.c errors.c input.c output.c parser.c scanner.c

clean:
	clear
	rm -rf *.o

go: 
	rm -rf *.o
	./main
