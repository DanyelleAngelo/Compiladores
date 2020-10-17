all: clean init clean go
	
init: libPascal.a
	gcc main_p.c -o main_p libPascal.a

libPascal.a: pascal
	ar rcs libPascal.a pascal.o

pascal: pascal.c pascal.h
	gcc -c pascal.c

clean:
	rm -rf *.o

go:
	./main_p