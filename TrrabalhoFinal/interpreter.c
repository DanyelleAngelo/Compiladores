#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "interpreter.h"

void init(){
	initVar();
	nextChar();
}

void initVar(){
	var = (int*)calloc(MAXVAR, sizeof(int));
}

void nextChar(){
	lookahead = getchar();
}

void newLine(){
	if(lookahead == '\n')nextChar();
}

void error(char *fmt, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args,fmt);
    vfprintf(stderr, fmt, args);
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
	fputs(" expected!\n",stderr);
	exit(1);
}

void match(char c){
	if(lookahead != c) expected("'%c'",c);
	nextChar();
}

char getName(){
	char name;

	if(!isalpha(lookahead)) expected("Identifier");

	name = toupper(lookahead);
	nextChar();

	return name;
}

int getNum(){
	int i = 0;

	if(!isdigit(lookahead)) expected("Integer");
	
	while(isdigit(lookahead)){
		i*=10;
		i+= lookahead - '0';
		nextChar();
	}

	return i;
}

void emit(char *fmt, ...){
	va_list  args;

	putchar('\t');
	va_start(args, fmt);
    vprintf(fmt, args);
	va_end(args);
	putchar('\n');
}

int expression(){
	int val;

	if(isAddOp(lookahead))val = 0;
	else val = term();

	while(isAddOp(lookahead)){
		switch(lookahead){
			case '+':
				match('+');
				val += term();
				break;
			case '-':
				match('-');
				val -= term();
				break;
		}
	}
	return val;
}

int term(){
	int val;

	val = factor();
	
	while(isMulOp(lookahead)){
		switch(lookahead){
			case '*':
				match('*');
				val *= factor();
				break;
			case '/':
				match('/');
				val /= factor();
				break;
		}
	}

	return val;
}

int factor(){
	int val;
	if(lookahead == '('){
		match('(');
		val = expression();
		match(')');
	}else if(isalpha(lookahead)){
		val = var[getName() - 'A'];
	}
	else{
		val = getNum();
	}

	return val;
}

void assignment(){
	char identifier;
	identifier= getName();
	match('=');
	var[identifier - 'A'] = expression();
	
}

int isAddOp(char c){
	return (c == '-' || c == '+');
}

int isMulOp(char c){
	return (c == '*' || c == '/');
}

void input(){
    char name;
    char buffer[20];

    match('?');
    name = getName();
    printf("%c? ", name);
    fgets(buffer, 20, stdin);

    var[name - 'A'] = atoi(buffer);
}

void output(){
	char name;
	match('!');
	name = getName();
	printf("%c -> %d", name, var[name - 'A']);
}