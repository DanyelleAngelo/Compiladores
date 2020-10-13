#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "cradle.h"

void init(){
	labelCount =0;
	nextChar();
}

void other(){
	emit("# %c", getName());
}

void programa(){
	block(-1);
	if(lookahead != 'e')expected("End");
	emit("END");
}

void block(int exitLabel){
	int follow = 0;

	while(!follow){
		newLine();
		switch(lookahead){
			case 'i':
				doIf(exitLabel);
				break;
			case 'w':
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
				break;
			case 'e':
			case 'l':
			case 'u':
				follow = 1;
				break;
			default:
				assignment();
				break;
		}
		newLine();
	}
}

void newLine(){
    if (look == '\n')nextChar();
}

int newLabel(){
	return labelCount++;
}

int postLabel(int lbl){
	printf("L%d:\n", lbl);
}

void doBreak(int exitLabel){
	match('b');

	if(exitLabel == -1 )fatal("No loop to break from");
	emit("JMP L%d",exitLabel);
}

void doIf(int exitLabel){
	int l1,l2;

	match('i');
	boolExpression();
	l1 = newLabel();//emite um rótulo para o comando
	l2 = l1;
	
	emit("JZ L%d",l1);
	block(exitLabel);
	if(lookahead == 'l'){//l = else
		match('l');
		l2 = newLabel();
		emit("JMP L%d",l2);
		postLabel(l1);
		block(exitLabel);
	}
	match('e');
	postLabel(l2);

}

void doWhile(){
	int l1, l2;

	match('w');
	l1= newLabel();
	l2 = newLabel();
	postLabel(l1);
	boolExpression();
	emit("JZ L%d",l2);
	block(l2);
	match('e');
	emit("JMP L%d",l1);
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
	 emit("JMP L%d",l1);
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
	emit("JZ L%d",l1);
	postLabel(l2);
}

void doFor(){
	int l1,l2;
	char name;

	match('f');
	l1 = newLabel();
	l2 = newLabel();
	
	name = getName();
	match('=');

	expression();
	emit("DEC AX");
	emit("MOV [%c], AX",name);

	expression();
	emit("PUSH AX");
	postLabel(l1);
	emit("MOV AX, [%c]",name);
	emit("INC AX");
	emit("MOV [%c], AX",name);
	emit("POP BX");
	emit("PUSH BX");
	emit("CMP AX, BX");
	emit("JG L%d",l2);
	block(l2);
	match('e');
	emit("JMP L%d",l1);
	postLabel(l2);
	emit("POP AX");
}

void doDo(){
	int l1,l2;

	match('d');
	l1 = newLabel();
	l2 = newLabel();
	expression();
	emit("MOV CX, AX");
	postLabel(l1);
	emit("PUSH CX");
	block(l2);
	emit("POP CX");
	emit("LOOP L%d",l1);
	emit("PUSH CX");
	postLabel(l2);
	emit("POP CX");
}

void nextChar(){
	lookahead = getchar();
}

void error(char *fmt, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args,fmt);
    vfprintf(stderr, fmt, args);
	va_end(args);

	fputc('\n',stderr);
}

void fatal(char *fmt, ...){
	va_list args;

	fputs("Error: ", stderr);
	va_start(args,fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);
	fputc('\n',stderr);
	exit(1);
}

void expected(char *fmt, ...){
	va_list args;
	fputs("Error: ", stderr);
	va_start(args, fmt);
	vfprintf(stderr,fmt,args);
	va_end(args);
	fputs(" expected!\n",stderr);
	exit(1);
}

void match(char c){
	if(lookahead != c) expected("'%c'",c);

	nextChar();
}

char getName(){
	char identifierName;

	if(!isalpha(lookahead)) expected("Identifier");

	identifierName = toupper(lookahead);
	nextChar();

	return identifierName;
}

char getNum(){
	char n;

	if(!isdigit(lookahead)) expected("Digit");

	n = lookahead;
	nextChar();

	return n;
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
	term();
	
	while(isAddOp(lookahead)){
		emit("PUSH AX");
		switch(lookahead){
			case '+':
				add();
				break;
			case '-':
				subtract();
				break;
			default:
				expected("Operation");
				break;
		}
	}
}

void term(){
	signedFactor();
	while(isMulOp(lookahead)){
		emit("PUSH AX");
		switch(lookahead){
			case '*':
				multiply();
				break;
			case '/':
				divide();
				break;
			default:
				emit("Operation!");
				break;
		}
	}
}

void factor(){
	if(lookahead == '('){
		match('(');
		boolExpression();
		match(')');
	}
	else if(isalpha(lookahead)) ident();
	else emit("MOV AX, %c", getNum());
	
}

void signedFactor(){
	if(lookahead == '+')nextChar();
	if(lookahead == '-'){
		nextChar();
		if(isdigit(lookahead))emit("MOV AX, - %c",getNum());
		else{
			factor();
			emit("NEG AX");
		}
	}else factor();
}

void ident(){
	char name;
	name = getName();
	if(lookahead == '('){
		match('(');
		match(')');
		emit("CALL %c", name);
	}else emit("MOV AX, [%c]", name);
}

void assignment(){
	char name;
	name = getName();
	match('=');
	boolExpression();
	emit("MOV [%c], AX",name);
}

void relation(){
	expression();
	if(isRelOp(lookahead)){
		emit("PUSH AX");
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
		emit("PUSH AX");
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
	if(getBoolean())emit("MOV AX, -1");
	else emit("MOV AX, 0");
}

void boolFactor(){
	if(isBoolean(lookahead)){
		if(getBoolean)emit("MOV AX, -1");
		else emit("MOV AX, 0");
	}else relation();
}

void boolTerm(){
	noFactor();
	while(lookahead == '&'){
		emit("PUSH AX");
		match('&');
		noFactor();
		emit("POP BX");
		emit("AND AX, BX");
	}
}

void noFactor(){
	if(lookahead == '!'){
		match('!');
		boolFactor();
		emit("NOT AX");
	}else boolFactor();
}

void boolOr(){
	match('|');
	boolTerm();
	emit("POP BX");
	emit("OR AX, BX");
}

void boolXor(){
	match('~');
	boolTerm();
	emit("POP BX");
	emit("XOR AX, BX");
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
	emit("POP BX");
	emit("CMP BX, AX");
	emit("JE L%d",l1);
	emit("MOV AX, 0");
	emit("JMP L%d",l2);
	postLabel(l1);
	emit("MOV AX, -1");
	postLabel(l2);
}

void notEquals(){
	int l1,l2;

	match('#');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	emit("POP BX");
	emit("CMP BX, AX");
	emit("JNE L%d",l1);
	emit("MOV AX, 0");
	emit("JMP L%d",l2);
	postLabel(l1);
	emit("MOV AX, -1");
	postLabel(l2);	
}

void greater(){
	int l1,l2;

	match('>');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	emit("POP BX");
	emit("CMP BX, AX");
	emit("JG L%d",l1);
	emit("MOV AX, 0");
	emit("JMP L%d",l2);
	postLabel(l1);
	emit("MOV AX, -1");
	postLabel(l2);
}

void less(){
	int l1,l2;

	match('<');
	l1 = newLabel();
	l2 = newLabel();

	expression();
	emit("POP BX");
	emit("CMP BX, AX");
	emit("JL L%d",l1);
	emit("MOV AX, 0");
	emit("JMP L%d",l2);
	postLabel(l1);
	emit("MOV AX, -1");
	postLabel(l2);	
}

void multiply(){
	match('*');
	factor();
    emit("POP BX");
    emit("IMUL BX");
}

void divide(){
	match('/');
	factor();
	emit("POP BX");
	emit("XCHG AX, BX");
	emit("CWD");
	emit("IDIV BX");

} 

void add(){
	match('+');
	term();
	emit("POP BX");
	emit("ADD AX, BX");
}

void subtract(){
	match('-');
	term();
	emit("POP BX");
	emit("SUB AX, BX");
    emit("NEG AX");
}