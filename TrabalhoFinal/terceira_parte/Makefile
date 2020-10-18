all: clean init go

init: librarys
	gcc main.c -o main libTiny.a libList.a

librarys: libList libTiny

libList: list
	ar rcs libList.a list.o

libTiny: tiny
	ar rcs libTiny.a tiny.o

list: list.c list.h
	gcc -c list.c 

tiny: tiny.c tiny.h
	gcc -c tiny.c

clean:
	clear
	rm -rf *.o

go: 
	./main
