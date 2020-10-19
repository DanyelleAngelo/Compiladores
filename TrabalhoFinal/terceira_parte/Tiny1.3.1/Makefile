all: clean init go

init: library
	gcc main.c -o main libTiny.a 

library: list tiny
	ar rcs libTiny.a list.o alloc.o asmCode.o errors.o input.o output.o parser.o scanner.o


list: manage/list.c manage/list.h
	gcc -c manage/list.c 

tiny: controller/alloc.c controller/alloc.h controller/asmCode.c controller/asmCode.h view/errors.c view/errors.h manage/input.c manage/input.h view/output.c view/output.h controller/parser.c controller/parser.h controller/scanner.c controller/scanner.h
	gcc -c controller/alloc.c controller/asmCode.c view/errors.c manage/input.c view/output.c controller/parser.c controller/scanner.c

clean:
	clear
	rm -rf *.o

go: 
	rm -rf *.o
	./main
