#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

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

int getNum(){
	int num =0;

	if(!isdigit(lookahead)) expected("Integer");

	while(isdigit(lookahead)){
		num *=10;
		num += lookahead - '0';
		nextChar();
	}
	return num;
}

int isAddOp(char c){
	return (c == '-' || c == '+');
}

int isMulOp(char c){
	return (c == '*' || c == '/');
}

void allocVar(char name){
	int value = 0, signal = 1;
	if(lookahead == '='){
		match('=');
		if(lookahead == '-'){
			match('-');
			signal = -1;
		}
		value = signal * getNum();
	}
	printf("%c:\tdw %d\n",name,value);
}

void prog(){
	match('p');
	header();
	topDecls();
	mainBlock();
	match('.');
}

void header(){
	printf(".model small\n");
	printf(".stack\n");
	printf(".code\n");
	printf("PROG segment byte public\n");
	printf("\tassume cs:PROG,ds:PROG,es:PROG,ss:PROG\n");
}

void topDecls(){
	while(lookahead!='b'){
		switch(lookahead){
			case 'v':
				decl();
				break;
			default:
				error("Unrecogmized keyword.");
				expected("BEGIN");
				break;
		}
	}
}

void decl(){
	match('v');
	for(;;){
		allocVar(getName());
		if(lookahead != ',')break;
		match(',');//quando declarado mais de uma variável por vez as mesma devem ser separadas por ","	
	}
}

void mainBlock(){
	match('b');
	prolog();
	match('e');
	epilog();
}

void prolog(){
	printf("MAIN:\n");
	printf("\tmov ax, PROG\n");
	printf("\tmov ds, ax\n");
	printf("\tmov es, ax\n");
}

void epilog(){
	printf("\tmov ax, 4C00h\n");
	printf("\tint 21h\n");
	printf("PROG ends\n");
	printf("\tend MAIN\n");
}