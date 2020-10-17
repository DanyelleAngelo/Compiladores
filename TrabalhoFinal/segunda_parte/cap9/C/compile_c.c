#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "compile_c.h"

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
	/*while(lookahead != EOF){
		switch(lookahead){
			case '#':
				preProc();
				break;
			case 'i':
				intDecl();
				break;
			case 'c':
				charDecl();
				break;
			default:
				doFunction();
				break;
		}
	}*/
}


void preProc(){}

void intDecl(){}

void charDecl(){}

void doFunction(char name){
	match('(');
	match(')');
	match('{');
	match('}');
	if(cur_type == ' ')cur_type = 'i';
	printf("Class: %c, Sign %c, Type: %c, Function: %c\n",cur_class, cur_sign,cur_type,name);
}


void getClass(){
	/*
		a = auto
		x = extern
		s = static

	*/
	if(lookahead =='a' || lookahead == 'x' || lookahead=='s'){
		cur_class = lookahead;
		nextChar();
	}
	else cur_class = 'a';
}

void getType(){
	cur_type = ' ';
	if(lookahead == 'u'){
		cur_sign = 'u';
		cur_type = 'i';
		nextChar();
	} else cur_sign = 's';
	if(lookahead == 'i' || lookahead == 'l' || lookahead == 'c'){
		cur_type = lookahead;
		nextChar();
	}
}

void topDecl(){
	char name;
	name = getName();
	if(lookahead == '(')doFunction(name);
	else doData(name);
}

void doData(char name){
	if(cur_type == ' ')expected("Type Declaration");
	for(;;){
		printf("Class: %c, Sign %c, Type: %c, Data: %c\n",cur_class, cur_sign,cur_type,name);
		if(lookahead != ',')break;
		match(',');
		name = getName();
	}
	match(',');
}