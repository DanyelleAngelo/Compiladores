all: clean init go

init: librarySingle 
	gcc main.c -o main librarySingle.a

librarySingle: input output errors scanner
	ar rcs librarySingle.a input.o output.o errors.o scanner1.o

input: ../input.c ../input.h
	gcc -c ../input.c

output: ../output.c ../output.h
	gcc -c ../output.c

errors: ../errors.c ../errors.h
	gcc -c ../errors.c

scanner: scanner1.c scanner1.h
	gcc -c scanner1.c 

clean:
	rm -rf *.o

go:
	./main