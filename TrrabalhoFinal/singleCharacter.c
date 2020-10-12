#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

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
	char identifierName;

	if(!isalpha(lookahead)) expected("Identifier");

	identifierName = toupper(lookahead);
	nextChar();

	return identifierName;
}

char getNum(){
	char n;

	if(!isdigit(lookahead)) expected("Digit");

	n = lookahead;
	nextChar();

	return n;
}

void emit(char *fmt, ...){
	va_list  args;

	putchar('\t');
	va_start(args, fmt);
    vprintf(fmt, args);
	va_end(args);
	putchar('\n');
}

void expression(){
	if(isAddOp(lookahead))emit("XOR AX, AX");
	else term();
	
	while(isAddOp(lookahead)){
		emit("PUSH AX");
		switch(lookahead){
			case '+':
				add();
				break;
			case '-':
				subtract();
				break;
			default:
				expected("Operation");
				break;
		}
	}
}

void term(){
	factor();
	while(lookahead == '*' || lookahead == '/'){
		emit("PUSH AX");
		switch(lookahead){
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
			default:
				emit("Operation!");
				break;
		}
	}
}

void factor(){
	if(lookahead == '('){
		match('(');
		expression();
		match(')');
	}
	else if(isalpha(lookahead)) ident();
	else emit("MOV AX, %c", getNum());
	
}

void ident(){
	char name;
	name = getName();
	if(lookahead == '('){
		match('(');
		match(')');
		emit("CALL %c", name);
	}else emit("MOV AX, [%c]", name);
}

void assignment(){
	char name;
	name = getName();
	match('=');
	expression();
	emit("MOV [%c], AX",name);
}

int isAddOp(char c){
	return (c == '-' || c == '+');
}

void multiply(){
	match('*');
	factor();
    emit("POP BX");
    emit("IMUL BX");
}

void divide(){
	match('/');
	factor();
	emit("POP BX");
	emit("XCHG AX, BX");
	emit("CWD");
	emit("IDIV BX");

} 

void add(){
	match('+');
	term();
	emit("POP BX");
	emit("ADD AX, BX");
}

void subtract(){
	match('-');
	term();
	emit("POP BX");
	emit("SUB AX, BX");
    emit("NEG AX");
}