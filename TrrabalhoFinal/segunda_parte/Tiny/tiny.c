#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

void asm_allocvar(char name, char type){
	int bType;
	switch(type){
		case 'b':
		case 'w':
			bType = type;
			break;
		case 'l':
			bType = 'd';
			break;
	}	
	printf("%c d%c0\n",name,bType);
}

void asm_loadvar(char  name,char type){
	switch(type){
		case 'b':
			printf("\tmov al, %c\n",name);
			break;
		case 'w':
			printf("\tmov ax, %c\n",name);
			break;
		case 'l':
			printf("\tmov dx, word ptr [%c+2]\n", name);
			printf("\tmov ax, word ptr [%c]\n", name);
			break;
	}
}

void asm_storevar(char name,char type){
	switch(type){
		case  'b':
			printf("\tmov %c, al\n",name);
			break;
		case 'w':
			printf("\tmov %c, ax\n",name);
		case 'l':
			printf("\tmov word ptr [%c+2], dx\n", name);
			printf("\tmov word ptr [%c], ax\n", name);
			break;

	}
}

void asm_convert(char src,char dst){
	if(src == dst) return;
	if(src == 'b')printf("\tcbw\n");//convert byte to word
	if(dst == 'l')printf("\tcwd\n");//covert word to Dword
}

void init(){
	int i;
	for(i=0;i< SYMTBL_SZ;i++)symTbl[i]='?';
	nextChar();
	skipWhite();
}

void nextChar(){
	lookahead = getchar();
}

void skipWhite(){
	while (lookahead == ' ' || lookahead  == '\t'){
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

void notVar(char  name){
	fprintf(stderr, "Error: %c is not a variable\n",name);
}

void dumpTable(){
	int i;
	printf("Symbol table dump:\n");
	for(i=0;i<SYMTBL_SZ;i++){
		if(symTbl[i]!='?')printf("%c  = %c\n",i+'A',symTbl[i]);
	}
}

char symType(char name){
	return symTbl[name - 'A'];
}

char inTable(char name){
	return(symTbl[name-'A']!= '?');
}

void checkedUp(char name){
	if(inTable(name))duplicated(name);
}

void addSymbol(char name, char type){
	checkedUp(name);
	symTbl[name - 'A'] = type;

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

int isVarType(char c){
	return (c == 'b' || c == 'l'|| c == 'w');
}

char varType(char name){
	char type =  symType(name);
	if(!isVarType(type))notVar(name);
	return type;
}

char loadVar(char name){
	char type = varType(name);
	asm_loadvar(name,type);
	return type;
}

void storeVar(char name,char srcType){
	char varType = varType(name);
	asm_convert(srcType,varType);
	asm_storevar(name,varType);
}

void alloc(char name,char type){
	addSymbol(name, type);
	asm_allocvar(name, type);
}

void decl(){
	char type = lookahead;
	nextChar();
	alloc(getName(),type);
}

void topDecls(){
	while(lookahead!='B'){
		switch(lookahead){
			case 'b':
			case 'w':
			case 'l':
				decl();
				break;
			default:
				unrecognized(lookahead);
				break;
		}
		newLine();
	}
}

char expression(){
	return loadVar(getName());
}

void assignment(){
	char name = getName(),type;
	match('=');
	type = expression();
	storeVar(name,type);
}

void doBlock(){
	while(lookahead !='.'){
		assignment();
		newLine();
	}
}