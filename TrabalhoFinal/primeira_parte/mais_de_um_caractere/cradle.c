#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "cradle.h"

void init(){
	nextChar();
	skipWhite();
}

void nextChar(){
	lookahead = getchar();
}

void skipWhite(){
	while(lookahead == ' ' || lookahead == '\t')nextChar();
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
	skipWhite();
}

char getName(char *identifier){
	int i;

	if(!isalpha(lookahead)) expected("Identifier");

	for(i=0;isalnum(lookahead);i++){
		if(i>=MAX_NAME)fatal("Identifier is very long!");
		identifier[i] = toupper(lookahead);
		nextChar();
	}
	identifier[i] = '\0';
	skipWhite();
}

char getNum(char *number){
	int i;

	if(!isdigit(lookahead)) expected("Digit");

	for(i=0;isdigit(lookahead);i++){
		if(i>=MAX_NUM)fatal("Number is very long!");
		number[i] = lookahead;
		nextChar();
	}
	number[i] = '\0';
	skipWhite();
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
	char number[MAX_NUM + 1];
	if(lookahead == '('){
		match('(');
		expression();
		match(')');
	}
	else if(isalpha(lookahead)){ident();}
	else{
		getNum(number);
		emit("MOV AX, %s", number);
	}
	
}

void ident(){
	char identifier[MAX_NAME +1];
	getName(identifier);
	if(lookahead == '('){
		match('(');
		match(')');
		emit("CALL %s", identifier);
	}else emit("MOV AX, [%s]", identifier);
}

void assignment(){
	char identifier[MAX_NAME +1];
	getName(identifier);
	match('=');
	expression();
	emit("MOV [%s], AX",identifier);
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