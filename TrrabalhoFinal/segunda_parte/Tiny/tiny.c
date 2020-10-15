#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

void asm_clear(){
	printf("\txor ax, ax\n");
}

void asm_negative(){
	printf("\tneg ax\n");
}

void asm_loadconst(int i){
	printf("\tmov ax, %d\n", i);
}

void asm_loadvar(char name){
	if(!intable(name))undefined(name);
	printf("\tmov ax, word ptr %c\n", name);
}

void asm_push(){
	printf("\tpush ax\n");
}

void asm_popadd(){
	printf("\tpop bx\n");
	printf("\tadd ax, bx\n");
}

void asm_popsub(){
	printf("\tpop bx\n");
	printf("\tsub ax, bx\n");
	printf("\tneg ax\n");
}

void asm_popmul(){
	printf("\tpop bx\n");
	printf("\timul bx\n");
}

void asm_popdiv(){
	printf("\tpop bx\n");
	printf("\txchg ax, bx\n");
	printf("\tcwd\n");
	printf("\tidiv bx\n");
}

void asm_store(char name){
	if(!intable(name))undefined(name);
	printf("\tmov word ptr bx, ax\n");
}

void asm_not(){
	printf("\tnot ax\n");
}

void asm_popand(){
	printf("\tpop bx\n");
	printf("\tand ax, bx\n");
}

void asm_popor(){
	printf("\tpop bx\n");
	printf("\tor ax, bx\n");	
}

void asm_popxor(){
	printf("\tpop bx\n");
	printf("\txor ax, bx\n");
}

void asm_popcompare(){
	printf("\tpop bx\n");
	printf("\tcmp bx, ax\n");	
}

void asm_relop(char op){
	char *jump;
	int l1,l2;
	l1 = newLabel();
	l2 = newLabel();

	switch(op){
		case '=':
			jump = "je";
			break;
		case '#':
			jump = "jne";
			break;
		case '<':
			jump = "jl";
			break;
		case '>':
			jump = "jg";
			break;
	}
	printf("\t%s L%d\n",jump,l1);
	printf("\txor ax, ax\n");
	printf("\tjmp L%d\n",l2);
	printf("L%d:\n",l1);
	printf("\tmov ax, -1\n");
	printf("L%d:\n",l2);
}

void asm_jmp(int label){
	printf("\tjmp L%d\n", label);
}

void asm_jmpfalse(int label){
	printf("\tjz L%d\n", label);
}

void asm_read(){}

void asm_write(){}

void init(){
	labelCount = 0;
	varTbl = calloc(VAR_TBL_SZ,sizeof(int));
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

int newLabel(){
	return labelCount++;
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

int isOrOp(char c){
	return (c == '|' || c == '~');
}

int isRelOp(char c){
	return (strchr("=#<>",c)!=NULL);
}

int intable(char name){
	return (varTbl[name - 'A'] != 0);
}

void undefined(char name){
	fprintf(stderr, "Error: Undefinied identifier %c\n",name);
	exit(1);
}

void allocVar(char name){
	int value = 0, signal = 1;

	if(intable(name)){
		fprintf(stderr, "Duplicate variable name: %c\n", name);
		exit(1);
	}else{
		varTbl[name - 'A'] = 1;
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

void block(){
	int follow = 0;
	while(!follow){
		switch(lookahead){
			case 'i':
				doIf();
				break;
			case 'w':
				doWhile();
				break;
			case 'e':
			case 'l':
				follow = 1;
				break;
			default:
				assignment();
				break;
		}
	}
}

void term1(){
	while(isMulOp(lookahead)){
		asm_push();
		switch(lookahead){
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
		}
	}
}

void term(){
	factor();
	term1();
}

void firstTerm(){
	firstFactor();
	term1();
}

void expression(){
	firstTerm();
	while(isAddOp(lookahead)){
		asm_push();
		switch(lookahead){
			case '+':
				add();
				break;
			case '-':
				subtract();
				break;
		}
	}
}


void factor(){
	if(lookahead == '('){
		match('(');
		//expression();
		boolExpression();
		match(')');
	}else if(isalpha(lookahead)){
		asm_loadvar(getName());
	}else{
		asm_loadconst(getNum());
	}
}

void negFactor(){
	match('-');
	if(isdigit(lookahead)){
		asm_loadconst(-getNum());
	}else{
		factor();
		asm_negative();
	}
}

void firstFactor(){
	switch(lookahead){
		case '+':
			match('+');
			factor();
			break;
		case '-':
			match('-');
			factor();
			break;
		default:
			factor();
			break;
	}
}

void assignment(){
	char name = getName();
	match('=');
	//expression();
	boolExpression();
	asm_store(name);
}

void relation(){
	char op;
	expression();
	if(isRelOp(lookahead)){
		op = lookahead;
		match(op);
		asm_push();
		expression();
		asm_popcompare();
		asm_relop(op);
	}
}

void notFactor(){
	if(lookahead == '!'){
		match('!');
		relation();
		asm_not();
	}else relation();
}

void boolTerm(){
	notFactor();
	while(lookahead == '&'){
		asm_push();
		match('&');
		notFactor();
		asm_popand();
	}
}

void boolExpression(){
	boolTerm();
	while(isOrOp(lookahead)){
		asm_push();
		switch(lookahead){
			case '|':
				boolOr();
				break;
			case '~':
				boolXor();
				break;
		}
	}
}

void boolOr(){
	match('|');
	boolTerm();
	asm_popor();
}

void boolXor(){
	match('~');
	boolTerm();
	asm_popxor();
}

void add(){
	match('+');
	term();
	asm_popadd();
}

void subtract(){
	match('+');
	term();
	asm_popsub();
}

void multiply(){
	match('*');
	factor();
	asm_popmul();
}

void divide(){
	match('/');
	factor();
	asm_popdiv();
}

void doIf(){
	int l1,l2;
	match('i');
	boolExpression();
	l1 = newLabel();
	l2 = l1;

	asm_jmpfalse(l1);
	block();
	if(lookahead  == 'l'){
		match('l');
		l2 = newLabel();
		asm_jmp(l2);
		printf("L%d\n",l1);
		block();
	}
	printf("L%d\n",l2);
	match('e');
}

void doWhile(){
	int l1,l2;
	match('w');
	l1 = newLabel();
	l2 = newLabel();
	printf("L%d\n",l1);
	boolExpression();
	asm_jmpfalse(l2);
	block();
	match('e');
	asm_jmp(l1);
	printf("L%d\n",l2);
}

void mainBlock(){
	match('b');
	prolog();
	block();
	match('e');
	epilog();
}

void prog(){
	match('p');
	header();
	topDecls();
	mainBlock();
	match('.');
	free(varTbl);
}

void header(){
	printf(".model small\n");
	printf(".stack\n");
	printf(".code\n");
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