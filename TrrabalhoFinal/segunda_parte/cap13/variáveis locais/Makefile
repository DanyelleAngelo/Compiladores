all: clean init clean go
	
init: libTiny.a
	gcc main.c -o main libTiny.a

libTiny.a: tiny
	ar rcs libTiny.a tiny.o

tiny: tiny.c tiny.h
	gcc -c tiny.c

clean:
	rm -rf *.o

go:
	./main