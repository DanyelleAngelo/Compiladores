
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

	fputc("\n",stderr);
}

void fatal(char *fmt, ...){
	va_list args;

	fputs("Error: ", stderr);
	va_start(args,fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);
	fputc("\n",stderr);
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

char getName(){
	char identifierName;

	if(!isalpha(lookahead))expected("Identifier");
	identifierName = toupper(lookahead);
	nextChar();

	return identifierName;
}

char getNum(){
	char n;

	if(!isdigit(lookahead))expected("Digit");

	n = lookahead;
	nextChar();

	return n;
}

void emit(char *fmt, ...){
	va_list  args;

	putchar("\n");
	va_start(args,fmt);
    vprintf(fmt, args);
	va_end(args);
	putchar("\n");
}