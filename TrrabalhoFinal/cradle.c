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
				other();
				break;
		}
	}
}

int newLabel(){
	return labelCount++;
}

int postLabel(int lbl){
	printf("L%d:\n", lbl);
}

void condition(){
	emit("# condition");
}

void doBreak(int exitLabel){
	match('b');

	if(exitLabel == -1 )fatal("No loop to break from");
	emit("JMP L%d",exitLabel);
}

void doIf(int exitLabel){
	int l1,l2;

	match('i');
	condition();
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
	condition();
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
	condition();
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

void emit(char *fmt, ...){
	va_list  args;

	putchar('\t');
	va_start(args, fmt);
    vprintf(fmt, args);
	va_end(args);
	putchar('\n');
}

void expression(){
	emit("# EXPR");
	/*if(isAddOp(lookahead))emit("XOR AX, AX");
	else term();
	
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
	}*/
}

void term(){
	factor();
	while(lookahead == '*' || lookahead == '/'){
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
		expression();
		match(')');
	}
	else if(isalpha(lookahead)) ident();
	else emit("MOV AX, %c", getNum());
	
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
	expression();
	emit("MOV [%c], AX",name);
}

int isAddOp(char c){
	return (c == '-' || c == '+');
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