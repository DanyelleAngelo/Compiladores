#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "pascal.h"

void init(){
	nextChar();
}

void nextChar(){
	lookahead = getchar();
}

void error(char *s){
	fprintf(stderr, "Error: %s\n", s);
}

void fatal(char *s){
	error(s);
	exit(1);
}

void expected(char *s){
	fprintf(stderr, "Error: %s expected\n",s);
	exit(1);
}

void match(char c){
	char s[2];
	if(lookahead != c){
		s[0] = c;
		s[1] =  '\0';
		expected(s);
	}
	nextChar();
}

char getName(){
	char identifier;

	if(!isalpha(lookahead)) expected("Identifier");

	identifier = toupper(lookahead);
	nextChar();	
	return identifier;
}

char getNum(){
	char num;

	if(!isdigit(lookahead)) expected("Integer");

	num = lookahead;
	nextChar();	
	return num;
}

int isAddOp(char c){
	return (c == '-' || c == '+');
}

int isMulOp(char c){
	return (c == '*' || c == '/');
}

void prog(){
	char name;

	match('p'); 
	name = getName();
	prolog();
	doBlock(name);
	match('.');
	epilog(name);
}

void prolog(){
	printf(".model small\n");
	printf(".stack\n");
	printf(".code\n");
	printf("PROG segment byte public\n");
	printf("\tassume cs:PROG,ds:PROG,es:PROG,ss:PROG\n");
}

void epilog(char name){
	printf("exit_prog:\n");
	printf("\tmov  ax,4C00h\n");
	printf("\tint 21h\n");
	printf("\tPROG ends\n");
	printf("\tend %c \n",name);
}

void doBlock(char name){
	declaration();
	printf("%c:\n",name);
	statements();	
}

void declaration(){
	int valid;
	do{
		valid = 1;
		switch(lookahead){
			case 'l':
				labels();
				break;
			case 'c':
				constants();
				break;
			case 't':
				types();
				break;
			case 'v':
				variables();
				break;
			case 'p':
				doProcedure();
				break;
			case 'f':
				doFunction();
				break;
			default:
				valid = 0;
				break;
		}
	}while(valid);
}

void statements(){
	match('b');
	while(lookahead!='e')nextChar();
	match('e');
}

void labels(){
	match('l');
}

void constants(){
	match('c');
}

void types(){
	match('t');
}

void variables(){
	match('v');
}

void doProcedure(){
	match('p');
}

void doFunction(){
	match('f');
}