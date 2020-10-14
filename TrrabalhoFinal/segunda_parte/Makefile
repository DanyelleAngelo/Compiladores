all: clean init clean go
	
init: libCradle.a
	gcc main.c -o main libCradle.a

libCradle.a: pascal
	ar rcs libCradle.a cradle.o

cradle: cradle.c cradle.h
	gcc -c cradle.c

clean:
	rm -rf *.o

go:
	./main