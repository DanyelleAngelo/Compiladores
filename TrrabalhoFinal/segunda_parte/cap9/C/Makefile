all: clean init clean go
	
init: libC.a
	gcc main.c -o main libC.a

libC.a: compile_c
	ar rcs libC.a compile_c.o

compile_c: compile_c.c compile_c.h
	gcc -c compile_c.c

clean:
	rm -rf *.o

go:
	./main