#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#include "cradle.h"

char *symtbl[SYMTBL_SZ];
char *kwlist[KWLIST_SZ] = {"IF", "ELSE", "ENDIF", "END"};
const char *kwcode = "ilee";

void init(){
	labelCount =0;
	nextChar();
	skipWhite();
}

void other(){
	//printf("# %c", getName());
}

void condition(){
	printf("\t## condition ##\n");
}

void programa(){
	block();
	matchstring("END");
	printf("\tint 2h\n");
}

void block(){
	int follow = 0;

	do{
		scan();
		switch(token){
			case 'i':
				doIf();
				break;
			/*case 'w':
				doWhile();
				break;
			case 'p':
				doLoop();
				break;
			case 'r':
				doRepeat();
				break;
			case 'f':
				doFor();
				break;
			case 'd':
				doDo();
				break;
			case 'b':
				doBreak(exitLabel);
				break;*/
			case 'e':
			case 'l':
			//case 'u':
				follow = 1;
				break;
			default:
				assignment();
				break;
		}
	}while(!follow);
}

void newLine(){
    if (lookahead == '\n')nextChar();
    skipWhite();
}

int newLabel(){
	return labelCount++;
}

int postLabel(int lbl){
	printf("L%d:\n", lbl);
}

void doBreak(){
	match('b');

	//if(exitLabel == -1 )fatal("No loop to break from");
	//printf("JMP L%d",exitLabel);
}

void doIf(){
	int l1,l2;

	condition();
	l1 = newLabel();//printfe um rótulo para o comando
	l2 = l1;
	
	printf("\tjz L%d\n", l1);
	block();
	if(token == 'l'){//l = else
		l2 = newLabel();
		printf("\tjmp L%d\n", l2);
		printf("L%d:\n", l1);
		block();
	}
	printf("L%d:\n", l2);
	matchstring("ENDIF");
}

void doWhile(){
	int l1, l2;

	match('w');
	l1= newLabel();
	l2 = newLabel();
	postLabel(l1);
	boolExpression();
	printf("JZ L%d",l2);
	block(l2);
	match('e');
	printf("JMP L%d",l1);
	postLabel(l2);
}

void doLoop(){
	 int l1,l2;

	 match('p');
	 l1 = newLabel();
	 l2 = newLabel();//para a instrução break
	 postLabel(l1);
	 block(l2);
	 match('e');
	 printf("JMP L%d",l1);
	 postLabel(l2);
}

void doRepeat(){
	int l1,l2;

	match('r');
	l1 = newLabel();
	l2 = newLabel();
	postLabel(l1);
	block(l2);
	match('u');
	boolExpression();
	printf("JZ L%d",l1);
	postLabel(l2);
}

void doFor(){
	int l1,l2;
	char name;

	match('f');
	l1 = newLabel();
	l2 = newLabel();
	
	getName();
	match('=');

	expression();
	printf("DEC AX");
	printf("MOV [%c], AX",name);

	expression();
	printf("PUSH AX");
	postLabel(l1);
	printf("MOV AX, [%c]",name);
	printf("INC AX");
	printf("MOV [%c], AX",name);
	printf("POP BX");
	printf("PUSH BX");
	printf("CMP AX, BX");
	printf("JG L%d",l2);
	block(l2);
	match('e');
	printf("JMP L%d",l1);
	postLabel(l2);
	printf("POP AX");
}

void doDo(){
	int l1,l2;

	match('d');
	l1 = newLabel();
	l2 = newLabel();
	expression();
	printf("MOV CX, AX");
	postLabel(l1);
	printf("PUSH CX");
	block(l2);
	printf("POP CX");
	printf("LOOP L%d",l1);
	printf("PUSH CX");
	postLabel(l2);
	printf("POP CX");
}

int lookup(char *s, char *list[], int size){
	int i;
	for (i=0; i < size; i++){
		if (strcmp(list[i], s) == 0)return i;
	}
	return -1;
}

void scan(){
	int kw;
	
	getName();
	
	kw = lookup(value, kwlist,KWLIST_SZ);
	if(kw == -1)token = 'x';
    else token = kwcode[kw];
}

void nextChar(){
	lookahead = getchar();
}

void skipWhite(){
	while(lookahead == ' ' || lookahead == '\t')nextChar();
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

void matchstring(char *s){
    if (strcmp(value, s) != 0)expected(s);
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

void getOp(){
	int i;
	if (!isOp(lookahead))expected("Operator");
	for (i = 0; isOp(lookahead) && i < MAX_OP; i++){
		value[i] = lookahead;
		nextChar();
	}
	value[i] = '\0';
	if(strlen(value)==1)token  = value[0];
	else token = '?';
}

void getName(){
	int i,kw;

	while(lookahead  == '\n')newLine();

	if(!isalpha(lookahead)) expected("Identifier");

	for(i=0;isalnum(lookahead)&& i<MAX_NAME;i++){
		value[i] = toupper(lookahead);
		nextChar();	
	}
	value[i] = '\0';
	token = 'x';
	skipWhite();
}

void getNum(){
	int i;

	if(!isdigit(lookahead)) expected("Integer");

	for(i=0;isdigit(lookahead)&& i<MAX_NUM;i++){
		value[i] = lookahead;
		nextChar();	
	}
	value[i] = '\0';
	token = '#';
	skipWhite();
}

int getBoolean(){
	int boolean;

	if(!isBoolean(lookahead))expected("Boolean Literal");
	boolean = (lookahead == 'T');
	nextChar();

	return boolean;
}

void emit(char *fmt, ...){
	va_list  args;

	putchar('\t');
	va_start(args, fmt);
    vprintf(fmt, args);
	va_end(args);
	putchar('\n');
}

void expression(){
	firstterm();
	
	while(isAddOp(lookahead)){
		printf("\tPUSH AX\n");
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

void firstterm(){
    signedFactor();
    term1();
}

void term(){
	factor();
	term1();
}

void term1(){
	while(isMulOp(lookahead)){
		printf("PUSH AX");
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

void factor(){
	if(lookahead == '('){
		match('(');
		expression();
		match(')');
	}
	else if(isalpha(lookahead)) ident();
	else{ 
		getNum();
		printf("\tmov ax, %s\n", value);
	}
	
}

void signedFactor(){
	int i;
	i = (lookahead == '-');

	if(isAddOp(lookahead)){
		nextChar();
		skipWhite();
	}
	factor();
	if(i)printf("\tneg ax\n");
}

void ident(){
	getName();
	if(lookahead == '('){
		match('(');
		match(')');
		printf("CALL %s", value);
	}else printf("MOV AX, [%s]", value);
}

void assignment(){
	char name[MAX_NAME+1];
	strcpy(name,value);
	match('=');
	expression();
	printf("\tlea bx, [%s]\n", name);
	printf("\tmov [bx], ax\n");
}

void relation(){
	expression();
	if(isRelOp(lookahead)){
		printf("PUSH AX");
		switch(lookahead){
			case '=':
				equals();
				break;
			case '#':
				notEquals();
				break;
			case '>':
				greater();
				break;
			case '<':
				less();
				break;
		}
	}
}

void boolExpression(){
	boolTerm();
	
	while(isOrOp(lookahead)){
		printf("PUSH AX");
		switch(lookahead){
			case '|':
				boolOr();
				break;
			case '~':
				boolXor();
				break;
		}
	}
	if(!isBoolean(lookahead))expected("Boolean Literal");
	if(getBoolean())printf("MOV AX, -1");
	else printf("MOV AX, 0");
}

void boolFactor(){
	if(isBoolean(lookahead)){
		if(getBoolean)printf("MOV AX, -1");
		else printf("MOV AX, 0");
	}else relation();
}

void boolTerm(){
	noFactor();
	while(lookahead == '&'){
		printf("PUSH AX");
		match('&');
		noFactor();
		printf("POP BX");
		printf("AND AX, BX");
	}
}

void noFactor(){
	if(lookahead == '!'){
		match('!');
		boolFactor();
		printf("NOT AX");
	}else boolFactor();
}

void boolOr(){
	match('|');
	boolTerm();
	printf("POP BX");
	printf("OR AX, BX");
}

void boolXor(){
	match('~');
	boolTerm();
	printf("POP BX");
	printf("XOR AX, BX");
}

int isOp(char c){
	return (strchr("+-*/<>:=", c) != NULL);
}

int isRelOp(char c){
	return (c == '=' || c =='#' || c == '<' || c== '>');
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

int isBoolean(char c){
	return(c == 'T' || c == 'F');
}

void equals(){
	int l1,l2;

	match('=');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	printf("POP BX");
	printf("CMP BX, AX");
	printf("JE L%d",l1);
	printf("MOV AX, 0");
	printf("JMP L%d",l2);
	postLabel(l1);
	printf("MOV AX, -1");
	postLabel(l2);
}

void notEquals(){
	int l1,l2;

	match('#');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	printf("POP BX");
	printf("CMP BX, AX");
	printf("JNE L%d",l1);
	printf("MOV AX, 0");
	printf("JMP L%d",l2);
	postLabel(l1);
	printf("MOV AX, -1");
	postLabel(l2);	
}

void greater(){
	int l1,l2;

	match('>');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	printf("POP BX");
	printf("CMP BX, AX");
	printf("JG L%d",l1);
	printf("MOV AX, 0");
	printf("JMP L%d",l2);
	postLabel(l1);
	printf("MOV AX, -1");
	postLabel(l2);
}

void less(){
	int l1,l2;

	match('<');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	printf("POP BX");
	printf("CMP BX, AX");
	printf("JL L%d",l1);
	printf("MOV AX, 0");
	printf("JMP L%d",l2);
	postLabel(l1);
	printf("MOV AX, -1");
	postLabel(l2);	
}

void multiply(){
	match('*');
	factor();
    printf("POP BX");
    printf("IMUL BX");
}

void divide(){
	match('/');
	factor();
	printf("POP BX");
	printf("XCHG AX, BX");
	printf("CWD");
	printf("IDIV BX");

} 

void add(){
	match('+');
	term();
	printf("POP BX");
	printf("ADD AX, BX");
}

void subtract(){
	match('-');
	term();
	printf("POP BX");
	printf("SUB AX, BX");
    printf("NEG AX");
}