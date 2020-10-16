#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "tiny.h"

char *kwlist[KWLIST_SZ] = {"IF","ELSE","ENDIF","WHILE","ENDWHILE","VAR","END","READ","WRITE"};
char kwcode[KWLIST_SZ+1] = "ileweveRW";

void asm_clear(){
	printf("\txor ax, ax\n");
}

void asm_negative(){
	printf("\tneg ax\n");
}

void asm_loadconst(char *val){
	printf("\tmov ax, %s\n", val);
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
	printf("\tmov word ptr %s, ax\n",name);
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
	nextToken();
}

void nextChar(){
	lookahead = getchar();
}

void skipWhite(){
	while (isspace(lookahead))nextChar();	
}

/*
void newLine(){
	while(lookahead == '\n'){
		nextChar();
		skipWhite();
	}
}*/

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

/*void match(char c){
	char s[2];
	newLine();
	if(lookahead != c){
		s[0] = c;
		s[1] =  '\0';
		expected(s);
	}
	nextChar();
	skipWhite();
}*/

void matchString(char *s){
	if(strcmp(value,s)!=0)expected(s);
	nextToken();
}

int lookaheadUp(char *s, char *list[], int size){
	int i;
	for(i=0;i<size;i++){
		if(strcmp(list[i],s)==0)return i;
	}
	return -1;
}

int locate(char *name){
	return lookaheadUp(name,symTbl,nSym);
}

void scan(){
	int kw;
	if(token == 'x'){
		kw = lookaheadUp(value,kwlist,KWLIST_SZ);
		if(kw >=0)token = kwcode[kw];
	} 
}

void getName(){
	int i;
	skipWhite();

	if(!isalpha(lookahead)) expected("Identifier or Keyword");
	for(i=0;isalnum(lookahead) && i<MAX_TOKEN;i++){
		value[i] = toupper(lookahead);
		nextChar();
	}
	value[i] =  '\0';
	token = 'x';
}

void getNum(){
	skipWhite();
	int i;

	if(!isdigit(lookahead)) expected("Integer");

	for(i=0;isdigit(lookahead) && i<MAX_TOKEN;i++){
		value[i] =  lookahead;
		nextChar();
	}
	value[i] = '\0';
	token  = '#';
}

void getOp(){
	skipWhite();
	token = lookahead;
	value[0] = lookahead;
	value[1] =  '\0';
	nextChar();
}

void nextToken(){
	skipWhite();
	if(isalpha(lookahead))getName();
	else if(isdigit(lookahead))getNum();
	else getOp();	
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

void checkIdent(){
	if(token != 'x')expected("Identifier");
}

void  duplicated(char *name){
	fprintf(stderr, "Duplicated variable name: %s\n",name );
	exit(1);
}

int intable(char *name){
	if(lookaheadUp(name,symTbl,nSym)<0)return 0;
	return 1;
}

void checkTable(char *name){
	if (!intable(name))undefined(name);
}

void checkedUp(char *name){
	if(intable(name))duplicated(name);
}

void addSymbol(char *name,char type){
	char *newSym;
	checkedUp(name);
	if(nSym >= SYMTBL_SZ){
		fatal("Symbol table full!");
	}
	newSym = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if(newSym == NULL)fatal("Out of memory!");
	strcpy(newSym,name);
	symTbl[nSym]=newSym;
	nSym++;
}

void allocVar(char *name, int value){
	/*int value = 0, signal = 1;

	if(lookahead == '='){
		match('=');
		newLine();	
		if(lookahead == '-'){
			match('-');
			signal = -1;
		}
		value = signal * getNum();
	}*/
	printf("%s:\tdw %d\n",name,value);
	
}

void topDecls(){
	scan();
	while(token == 'v'){
		do{
			decl();
		}while(token == ',');
	}
}

void decl(){
	nextToken();
	if(token !='x')expected("Variable name");
	checkedUp(value);
	addSymbol(value,'v');
	allocVar(value,0);
	nextToken();
}

void readVar(){
	checkIdent();
	checkTable(value);
	asm_read();
	nextToken();
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

void term(){
	factor();
	while(isMulOp(token)){
		asm_push();
		switch(token){
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
		}
	}
}

void expression(){
	if(isAddOp(token))asm_clear();
	else term();

	while(isAddOp(token)){
		asm_push();
		switch(token){
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
	if(token == '('){
		nextToken();
		boolExpression();
		matchString(")");
	}else{
		if(token == 'x')asm_loadvar(value);
		else if(token == '#')asm_loadconst(value);
		else expected("Math Factor");
		nextToken();
	}
}

/*void negFactor(){
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
}*/

void assignment(){
	char name[MAX_TOKEN+1];
	strcpy(name,value);
	checkTable(name);
	nextToken();
	matchString("=");
	boolExpression();
	asm_store(name);
}

void relation(){
	char op;
	expression();
	if(isRelOp(token)){
		op = token;
		nextToken();
		if(op == '<'){
			if(token == '>'){
				nextToken();
				op = '#';
			}else if(token == '='){
				nextToken();;
				op = 'L';
			}
		}else if(op == '>' && token == '='){
			nextToken();
			op = 'G';
		}
		asm_push();
		expression();
		asm_popcompare();
		asm_relop(op);
	}
}

void notFactor(){
	if(token == '!'){
		nextToken();
		relation();
		asm_not();
	}else relation();
}

void boolTerm(){
	notFactor();
	while(token == '&'){
		asm_push();
		nextToken();
		notFactor();
		asm_popand();
	}
}

void boolExpression(){
	boolTerm();
	while(isOrOp(token)){
		asm_push();
		switch(token){
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
	nextToken();
	boolTerm();
	asm_popor();
}

void boolXor(){
	nextToken();
	boolTerm();
	asm_popxor();
}

void add(){
	nextToken();
	term();
	asm_popadd();
}

void subtract(){
	nextToken();
	term();
	asm_popsub();
}

void multiply(){
	nextToken();
	factor();
	asm_popmul();
}

void divide(){
	nextToken();
	factor();
	asm_popdiv();
}

void doIf(){
	int l1,l2;
	nextToken();
	boolExpression();
	l1 = newLabel();
	l2 = l1;

	asm_jmpfalse(l1);
	block();
	if(token  == 'l'){
		nextToken();
		l2 = newLabel();
		asm_jmp(l2);
		printf("L%d\n",l1);
		block();
	}
	printf("L%d\n",l2);
	matchString("ENDIF");
}

void doWhile(){
	int l1,l2;
	nextToken();
	l1 = newLabel();
	l2 = newLabel();

	printf("L%d\n",l1);
	boolExpression();
	asm_jmpfalse(l2);
	block();
	matchString("ENDWHILE");
	asm_jmp(l1);
	printf("L%d\n",l2);
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
	nextToken();
	matchString("(");
	for(;;){
		readVar();
		if(token != ',')break;
		nextToken();
	}
	matchString(")");
}

void doWrite(){
	nextToken();
	matchString("(");
	for(;;){
		expression();
		asm_write();
		if(token !=',')break;
		nextToken();
	}
	matchString(")");
}