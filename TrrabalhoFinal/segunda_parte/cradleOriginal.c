#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

#include "cradle.h"

void init(){
	nextChar();
}

void nextChar(){
	lookahead = getchar();
}

void error(char *fmt, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args,fmt);
	va_end(args);

	fputc('\n',stderr);
}

void fatal(char *fmt, ...){
	va_list args;

	fputs("Error: ", stderr);
	va_start(args,fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);
	fputc('\n',stderr);
	exit(1);
}

void expected(char *fmt, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args, fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);
	fputs("Expectd!\n",stderr);
	exit(1);
}

void match(char c){
	if(lookahead != c)expected("'%c'",c);
	nextChar();
}

void  getName(char *identifier){
	int i;
	if(!isalpha(lookahead)) expected("Identifier");

	for(i=0;isalnum(lookahead) && i<MAX_NAME;i++){
		identifier[i] = toupper(lookahead);
		nextChar();
	}
	identifier[i] = '\0'; 
}

void getNum(char *num){
	int i;

	if(!isdigit(lookahead)) expected("Integer");

	for(i=0;isdigit(lookahead) && i<MAX_NUM;i++){
		num[i] = lookahead;
		nextChar();
	}
	num[i] = '\0';
}


void emit(char *fmt, ...){
	va_list  args;

	putchar('\n');
	va_start(args,fmt);
    vprintf(fmt, args);
	va_end(args);
	putchar('\n');
}