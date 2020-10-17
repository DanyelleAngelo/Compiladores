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

void asm_loadconst(long num, char type){
	switch (type) {
		case 'b':
			printf("\tmov al, %d\n", (int) num);
			break;
		case 'w':
			printf("\tmov ax, %d\n", (int) num);
			break;
		case 'l':
			printf("\tmov dx, %lu\n", num >> 16);//coloca em dx os 16 bits mais significativos
			printf("\tmov ax, %lu\n", num & 0xFFFF);//pegas os  16 bit menos significativos
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

void asm_clear(){
	printf("\txor ax, ax\n");
}

void asm_push(char type){
	if(type=='b')printf("\tcbw\n");
	if(type=='l')printf("\tpush dx\n");
	printf("\tpush dax\n");
}

void asm_pop(char type){
	printf("\tpop bx\n");
	if (type == 'l')printf("\tpop cx\n");
}

void asm_swap(char type){
	printf("%c\n",lookahead);
	switch (type) {
		case 'b':
			printf("\txchg al, bl\n");
			break;
		case 'w':
			printf("\txchg ax, bx\n");
			break;
		case 'l':
			printf("\txchg ax, bx\n");
			printf("\txchg dx, cx\n");
			break;
		}
}

char asm_sametype(char t1, char t2, int order){
	int swaped = 0;
	char type = t1;
	if (t1 != t2) {
		if ((t1 == 'b') || (t1 == 'w' && t2 == 'l')) {
			type = t2;
			asm_swap(type);
			asm_convert(t1, t2);
			swaped = 1;
		} else {
			type = t1;
			asm_convert(t2, t1);
		}
    }	
    if (!swaped && order)asm_swap(type);
	return type;
}

char asm_popadd(char t1, char t2){
	char type;
	asm_pop(t1);
	type = asm_sametype(t1, t2,1);
	switch(type){
		case 'b':
			printf("\tadd al, bl\n");
			break;
		case 'w':
			printf("\tadd ax, bx\n");
			break;
		case 'l':
			printf("\tadd ax, bx\n");
			printf("\tadc dx, cx\n");
			break;
    }
    return type;
}

char asm_popsub(char t1, char t2){
	char type;
	asm_pop(t1);
	type = asm_sametype(t1, t2,0);
	switch (type) {
		case 'b':
			printf("\tsub al, bl\n");
			break;
		case 'w':
			printf("\tsub ax, bx\n");
			break;
		case 'l':
			printf("\tsub ax, bx\n");
			printf("\tsbb dx, cx\n");
			break;
    }
    return type;
}

char asm_popmul(char t1,char t2){
	char type, mulType = 'l';
	asm_pop(t1);
	type=asm_sametype(t1,t2,0);
	switch (type){
		case 'b':
			printf("\tmul bl\n");
			mulType = 'w';
			break;
		case 'w':
			printf("\tmul bx\n");
			break;
		case 'l':
			//biblioteca ("imaginária") que faz multiplicaçã de 32x32bits
			printf("\tcall MUL32\n");
			break;
	}
	return mulType;
}

char asm_popdiv(char t1,char t2){
	/*
	1. type(quociente) = type(dividendo)
	2. type(dividendo) = long então   type(divisor)=long
	3.divisão são confiáveis para dividendos do tipo byte ou word, se type(dividendo) ou type(divisor) = long 
	usar outra rotina que possa retornar um long long
	*/
	asm_pop(t1);
	if(t1=='l')asm_convert(t2, 'l');

	if(t1=='l' || t2=='l')asm_swap('l');
	else if(t1=='w' || t2=='w')asm_swap('w');
	else  asm_swap('b');

    if (t2 == 'b')asm_convert(t1, 'w');
	else asm_convert(t1, 'l');

    if (t1 == 'l' || t2 == 'l')printf("\tcall DIV32\n");//ponto 3
	else if (t2 == 'w')printf("\tidiv bx\n");//divisão confiável
	else if (t2 == 'b') printf("\tidiv bl\n");//divisão confiável

	return t1;//ponto 1
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

long getNum(){
	long num =0;
	if(!isdigit(lookahead)) expected("Integer");
	while(isdigit(lookahead)){
		num *=10;
		num += lookahead - '0';
		nextChar();
	}
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

char unOp(){
	asm_clear();
	return 'w';
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

char loadNum(long num){
	char type;
	if(num >=-128 && num<=127)type='b';
	else if(num>=-32768 && num<=32767)type='w';
	else type='l';
	asm_loadconst(num,type);
	return type;
}

void storeVar(char name,char srcType){
	char type = varType(name);
	asm_convert(srcType,type);
	asm_storevar(name,type);
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

char factor(){
	char type;
	if(lookahead =='('){
		match('(');
		type = expression();
		match(')');
	}else if(isalpha(lookahead))type = loadVar(getName());
	else type = loadNum(getNum());
	return type;
}

char term(){
	char type = factor();
	while(isMulOp(lookahead)){
		asm_push(type);
		switch(lookahead){
			case '*':
				type=multiply(type);
				break;
			case '/':
				type=divide(type);
				break;
		}
	}
	return type;
}

void assignment(){
	char name = getName(),type;
	match('=');
	type = term();
	storeVar(name,type);
}

char expression(){
	char type;
	if(isAddOp(lookahead))type = unOp();
	else  type=term();

	while(isAddOp(lookahead)){
		asm_push(type);
		switch(lookahead){
			case '+':
				type = add(type);
				break;
			case '-':
				type = subtract(type);
				break;
		}
	}
	return type;
}

void doBlock(){
	while(lookahead !='.'){
		assignment();
		newLine();
	}
}

char add(char type){
	match('+');
	return asm_popadd(type, term());
}

char subtract(char type){
	match('-');
	return asm_popsub(type, term());
}

char divide(char type){
	match('/');
	return asm_popdiv(type, factor());
}

char multiply(char type){
	match('*');
	return asm_popmul(type, factor());
}
