#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

void asm_allocvar(char name){
	if(inTable(name))duplicated(name);
	addSymbol(name,'v');
	printf("%c:\tdw 0\n",name);
}

void asm_loadvar(char name){
	if(!inTable(name))undefined(name);
	printf("\tmov ax, word ptr %c\n", name);
}

void asm_store(char name){
	printf("\tmov word ptr %c, ax\n",name);
}


void asm_return(){

}

void init(){
	int i;
	for(i=0;i< SYMTBL_SZ;i++)symTbl[i]=' ';
	nextChar();
	skipWhite();
}

void nextChar(){
	lookahead = getchar();
}


void skipWhite(){
	while (lookahead == ' ' || lookahead  == '\n'){
		nextChar();
	}	
}

void newLine(){
	while(lookahead == '\n'){
		nextChar();
	}
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

void undefined(char name){
	fprintf(stderr, "Error: Undefined identifier %c\n", name);
	exit(1);
}

void duplicated(char name){
	fprintf(stderr, "Error: Duplicated identifier %c\n", name);
	exit(1);
}

void unrecognized(char name){
	fprintf(stderr, "Error: Unrecognized keyword %c\n", name);
	exit(1);
}

void notVar(char name){
	fprintf(stderr, "Error: %c is not a variable\n", name);
	exit(1);
}

char symType(char name){
	return symTbl[name - 'A'];
}

char inTable(char name){
	return(symTbl[name-'A']!= ' ');
}

void addSymbol(char name, char type){
	if (inTable(name))duplicated(name);
	symTbl[name - 'A'] = type;

}

void checkvar(char name){
	if (!inTable(name))undefined(name);
	if (symType(name) != 'v')notVar(name);
}

void match(char c){
	char s[2];
	if(lookahead != c){
		s[0] = c;
		s[1] =  '\0';
		expected(s);
	}
	nextChar();
	skipWhite();
}

char getName(){
	char name;
	if(!isalpha(lookahead)) expected("Identifier or Keyword");
	name  = toupper(lookahead);
	nextChar();
	skipWhite();
	return name;
}

char getNum(){
	char num;
	if(!isdigit(lookahead)) expected("Integer");
	num = lookahead;
	nextChar();
	skipWhite();
	return num;
}

int isAddOp(char c){
	return (c == '-' || c == '+');
}

int isMulOp(char c){
	return (c == '*' || c == '/');
}

int isOrOp(char c){
	return (c == '|' || c == '~');
}

int isRelOp(char c){
	return (strchr("=#<>",c)!=NULL);
}


void topDecls(){
	while(lookahead != '.'){
		switch(lookahead){
			case 'v':
				decl();
				break;
			case 'p':
				doProc();
				break;
			case 'P':
				doMain();
				break;
			default:
				unrecognized(lookahead);
				break;
		}
		newLine();
	}
}

void decl(){
	match('v');
	asm_allocvar(getName());
}

void doBlock(){
	while(lookahead !='e'){
		assignment();
		newLine();
	}
}

void doProc(){
	char name;
	match('p');
	name =getName();
	newLine();
	if(inTable(name))duplicated(name);
	addSymbol(name,'p');
	printf("%c:\n",name);
	beginBlock();
	asm_return();
}

void beginBlock(){
	match('b');
	newLine();
	doBlock();
	match('e');
	newLine();
}

void expression(){
	asm_loadvar(getName());
}

void assignment(){
	char name  = getName();
	match('=');
	expression();
	asm_store(name);
}

void doMain(){
	char name;
	match('P');
	name = getName();
	newLine();
	if(inTable(name))duplicated(name);
	prolog();
	beginBlock();
}

void header(){
	printf(".model small\n");
	printf(".stack\n");
	printf(".code\n");
	printf("extrn READ:near, WRITE:near\n");
	printf("PROG segment byte public\n");
	printf("\tassume cs:PROG,ds:PROG,es:PROG,ss:PROG\n");
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