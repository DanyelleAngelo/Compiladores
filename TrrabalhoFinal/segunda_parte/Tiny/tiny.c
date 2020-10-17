#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

void asm_allocvar(char name){
	//if(inTable(name))duplicated(name);
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
	printf("\tret\n");
}

void asm_call(char name){
	printf("\tcall %c\n",name);
}

int asm_offsetpar(int par){
	int offset;
	offset = 4 + 2 *(nParams - par);
	return offset;	
}

void asm_loadparam(int par){
	printf("\tmov ax, word ptr [bp+%d]\n", asm_offsetpar(par));
}

void asm_storeparam(int par){
	printf("\tmov word ptr [bp+%d], ax\n", asm_offsetpar(par));
}

void asm_push(){
	printf("\tpush ax\n");
}

void asm_cleanstack(int bytes){
	if(bytes >0)printf("\tadd sp, %d\n",bytes);
}

void asm_procprolog(char name){
	printf("%c:\n", name);
	printf("\tpush bp\n");
	printf("\tmov bp, sp\n");
}

void asm_procepilog(){
	printf("\tpop bp\n");
	printf("\tret\n");
}

void init(){
	int i;
	for(i=0;i< SYMTBL_SZ;i++)symTbl[i]=' ';
	clearParams();
	nextChar();
	skipWhite();
}

void clearParams(){
	int i;
	for(i=0;i<PARAMS_SZ;i++)params[i]=0;
	nParams = 0;
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
	if(isParam(name))return 'f';
	return symTbl[name - 'A'];
}

char inTable(char name){
	return(symTbl[name-'A']!= ' ');
}

void addSymbol(char name, char type){
	if (inTable(name))duplicated(name);
	symTbl[name - 'A'] = type;

}

void addParam(char name){
	if(isParam(name))duplicated(name);
	params[name  -  'A'] = ++ nParams;	
}

int paramNum(char name){
	return params[name-'A'];
}

int isParam(char name){
	return(params[name-'A']!= 0);
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
		assignOrCall();
		newLine();
	}
}

void formalParam(){
	addParam(getName());
}

void formalList(){
	match('(');
	if(lookahead !=')'){
		//não é uma lista vazia
		formalParam();
		while(lookahead == ','){
			match(',');
			formalParam();
		}
	}
	match(')');
}

void param(){
	expression();
	asm_push();
}

int paramList(){
	int i =0;
	match('(');
	if(lookahead!= ')'){
		for(;;){
			param();
			i++;
			if(lookahead != ',')break;	
			match(',');
		}
	}
	match(')');
	return i*2;
}

void doCallProc(char name){
	int bytes = paramList();
	asm_call(name);
	asm_cleanstack(bytes);	
}

void doProc(){
	char name;
	match('p');
	name =getName();
	formalList();
	newLine();
	addSymbol(name,'p');
	asm_procprolog(name);
	beginBlock();
	asm_procepilog();
	clearParams();
}

void beginBlock(){
	match('b');
	newLine();
	doBlock();
	match('e');
	newLine();
}

void expression(){
	char name = getName();
	if(isParam(name))asm_loadparam(paramNum(name));
	else asm_loadvar(name);

}

void assignment(char name){
	match('=');
	expression();
	asm_store(name);
}

void assignOrCall(){
	char name  = getName();
	switch(symType(name)){
		case ' ':
			undefined(name);
			break;
		case 'v':
		case 'f':
			assignment(name);
			break;
		case 'p':
			doCallProc(name);
			break;
		default:
			printf("Identifier %c cannt be used here!\n",name);
			exit(1);
			break;
	}
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