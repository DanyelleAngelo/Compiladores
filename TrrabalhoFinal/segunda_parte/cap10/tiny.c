#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

char *kwlist[KWLIST_SZ] = {"IF","ELSE","ENDIF","WHILE","ENDWHILE","VAR","BEGIN","END","PROGRAM","READ","WRITE"};
char *kwcode = "ilewevbepRW";

void asm_clear(){
	printf("\txor ax, ax\n");
}

void asm_negative(){
	printf("\tneg ax\n");
}

void asm_loadconst(int i){
	printf("\tmov ax, %d\n", i);
}

void asm_loadvar(char *name){
	if(!intable(name))undefined(name);
	printf("\tmov ax, word ptr %s\n", name);
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

void asm_store(char *name){
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
	int l1 = newLabel(),l2 = newLabel();

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
		case 'L':
			jump = "jle";
			break;
		case 'G':
			jump = "jge";
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

void asm_read(){
	printf("\tcall READ\n");
	asm_store(value);
}

void asm_write(){
	printf("\tcall WRITE\n");
}

void init(){
	labelCount = 0;
	nSym = 0;
	//symTbl = calloc(SYMTBL_SZ,sizeof(char));
	nextChar();
	scan();
}

void nextChar(){
	lookahead = getchar();
}

void skipWhite(){
	while (lookahead == ' ' || lookahead == '\t')nextChar();	
}

void newLine(){
	while(lookahead == '\n'){
		nextChar();
		skipWhite();
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

int newLabel(){
	return labelCount++;
}

void match(char c){
	char s[2];
	newLine();
	if(lookahead != c){
		s[0] = c;
		s[1] =  '\0';
		expected(s);
	}
	nextChar();
	skipWhite();
}

void matchString(char *s){
	if(strcmp(value,s)!=0)expected(s);
}

int lookaheadUp(char *s, char *list[], int size){
	int i;
	for(i=0;i<size;i++){
		if(strcmp(list[i],s)==0)return i;
	}
	return -1;
}

void scan(){
	int kw;
	getName();
	kw = lookaheadUp(value,kwlist,KWLIST_SZ);
	if(kw==-1)token = 'x';
	else token = kwcode[kw];
}

void getName(){
	int i;
	newLine();

	if(!isalpha(lookahead)) expected("Identifier");
	for(i=0;isalnum(lookahead) && i<MAX_TOKEN;i++){
		value[i] = toupper(lookahead);
		nextChar();
	}
	value[i] =  '\0';
	token = 'x';
	skipWhite();
}

int getNum(){
	newLine();
	int num =0;

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

void undefined(char *name){
	fprintf(stderr, "Error: Undefinied identifier %s\n",name);
	exit(1);
}

int intable(char *name){
	if(lookaheadUp(name,symTbl,nSym)<0)return 0;
	return 1;
}

void addSymbol(char *name){
	char *newSym;
	if(intable(name)){
		fprintf(stderr, "Duplicated variable name: %s\n",name );
		exit(1);
	}
	if(nSym >= SYMTBL_SZ){
		fatal("Symbol table full!");
	}
	newSym = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if(newSym == NULL)fatal("Out of memory!");
	strcpy(newSym,name);
	symTbl[nSym++]=newSym;
}

void allocVar(char *name){
	int value = 0, signal = 1;

	addSymbol(name);
	newLine();
	if(lookahead == '='){
		match('=');
		newLine();	
		if(lookahead == '-'){
			match('-');
			signal = -1;
		}
		value = signal * getNum();
	}
	printf("%s:\tdw %d\n",name,value);
	
}

void topDecls(){
	scan();
	while(token!='b'){
		switch(token){
			case 'v':
				decl();
				break;
			default:
				error("Unrecogmized keyword.");
				expected("BEGIN");
				break;
		}
		scan();
	}
}

void decl(){
	for(;;){
		getName();
		allocVar(value);
		newLine();
		if(lookahead != ',')break;
		match(',');//quando declarado mais de uma variável por vez as mesma devem ser separadas por ","	
	}
}

void block(){
	int follow = 0;
	do{
		scan();
		switch(token){
			case 'i':
				doIf();
				break;
			case 'w':
				doWhile();
				break;
			case 'W':
				doWrite();
				break;
			case 'R':
				doRead();
				break;
			case 'e':
			case 'l':
				follow = 1;
				break;
			default:
				assignment();
				break;
		}
	}while(!follow);
}

void term1(){
	newLine();
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
		newLine();
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
	newLine();
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
		newLine();
	}
}

void factor(){
	newLine();
	if(lookahead == '('){
		match('(');
		//expression();
		boolExpression();
		match(')');
	}else if(isalpha(lookahead)){
		getName();
		asm_loadvar(value);
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
	newLine();
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
	char name [MAX_TOKEN+1];
	strcpy(name,value);
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
		if(op == '<'){
			if(lookahead == '>'){
				match('>');
				op = '#';
			}else if(lookahead == '='){
				match('=');
				op = 'L';
			}
		}else if(op == '>' && lookahead == '='){
			match('=');
			op = 'G';
		}
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
	newLine();
	while(lookahead == '&'){
		asm_push();
		match('&');
		notFactor();
		asm_popand();
		newLine();
	}
}

void boolExpression(){
	boolTerm();
	newLine();
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
		newLine();
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
	match('-');
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
	boolExpression();
	l1 = newLabel();
	l2 = l1;

	asm_jmpfalse(l1);
	block();
	if(token  == 'l'){
		l2 = newLabel();
		asm_jmp(l2);
		printf("L%d\n",l1);
		block();
	}
	printf("L%d\n",l2);
	matchString("ENDIF");
}

void doWhile(){
	int l1 = newLabel(),l2 = newLabel();

	printf("L%d\n",l1);
	boolExpression();
	asm_jmpfalse(l2);
	block();
	matchString("ENDWHILE");
	asm_jmp(l1);
	printf("L%d\n",l2);
}

void mainBlock(){
	matchString("BEGIN");
	prolog();
	block();
	matchString("END");
	epilog();
}

void prog(){
	matchString("PROGRAM");
	header();
	topDecls();
	mainBlock();
	match('.');
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

/*Criar uma biblioteca a parte*/
void doRead(){
	match('(');
	for(;;){
		getName();
		asm_read();
		newLine();
		if(lookahead != ',')break;
		match(',');
	}
	match(')');
}

void doWrite(){
	match('(');
	for(;;){
		expression();
		asm_write();
		newLine();
		if(lookahead !=',')break;
		match(',');
	}
	match(')');
}