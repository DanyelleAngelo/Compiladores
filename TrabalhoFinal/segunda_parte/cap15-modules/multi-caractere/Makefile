all: clean init go

init: libraryMulti
	gcc main.c -o main libraryMulti.a

libraryMulti: input output errors scanner parser codegen
	ar rcs libraryMulti.a input.o output.o errors.o scanner.o parser.o codegen.o

scanner: scanner.c scanner.h
	gcc -c scanner.c 

parser: parser.c parser.h
	gcc -c parser.c 

input: ../input.c ../input.h
	gcc -c ../input.c

output: ../output.c ../output.h
	gcc -c ../output.c

errors: ../errors.c ../errors.h
	gcc -c ../errors.c

codegen: ../codegen.c ../codegen.h
	gcc -c ../codegen.c 

clean:
	rm -rf *.o

go: clean
	./main