#include <ctype.h>
#include "parser.h"
#include "scanner.h"
#include "../input.h"
#include "../errors.h"
#include "../codegen.h"

void factor(){
	char name[MAX_NAME+1],num[MAX_NUM+1];
	if(lookahead== '('){
		match('(');
		expression();
		match(')');
	}else  if(isalpha(lookahead)){
		getName(name);
		asmLoadVariable(name);
	}else if(isdigit(lookahead)){
		getNum(num);
		asmLoadConstant(num);
	}else error("Unrecognized character: '%c'", lookahead);
}

void signedTerm(){
	char sign = lookahead;
	if(isAddOp(lookahead))nextChar();
	term();
	if(sign == '-')asmNegate();
}

void term(){
	factor();
	while(isMulOp(lookahead)){
		switch(lookahead){
			case'*':
				multiply();
				break;
			case '/':
				divide();
				break;
		}
	}
}

void expression(){
	signedTerm();
	while(isAddOp(lookahead)){
		switch(lookahead){
			case'+':
				add();
				break;
			case '-':
				subtract();
				break;
		}
	}
}

void assignment(){
	char name[MAX_NAME+1];
	getName(name);
	match('=');
	expression();
	asmStoreVariable(name);
}

void add(){
	match('+');
	asmPush();
	factor();
	asmPopAdd();
}

void subtract(){
	match('-');
	asmPush();
	factor();
	asmPopSub();
}

void multiply(){
	match('*');
	asmPush();
	factor();
	asmPopMul();
}

void divide(){
	match('/');
	asmPush();
	factor();
	asmPopDiv();
}