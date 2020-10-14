#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "cradle.h"

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