#include<stdio.h>
#include "asmCode.h"
#include "output.h"

void asm_clear(){
	emit("\tXOR AX, AX\n");
}

void asm_negative(){
	emit("NEG AX");
}

void asm_loadconst(char *val){
	emit("\tMOV AX, %s\n", val);
}

void asm_loadvar(char *name){
	emit("\tMOV AX, WORD PTR %s\n", name);
}

void asm_push(){
	emit("\tPUSh AX\n");
}

void asm_popadd(){
	emit("\tPOP BX\n");
	emit("\tADD AX, BX\n");
}

void asm_popsub(){
	emit("\tPOP BX\n");
	emit("\tSUB AX, BX\n");
	emit("\tNEG AX\n");
}

void asm_popmul(){
	emit("\tPOP BX\n");
	emit("\tIMUl BX\n");
}

void asm_popdiv(){
	emit("\tPOP BX\n");
	emit("\tXCHg AX, BX\n");
	emit("\tCWD\n");
	emit("\tIDIv BX\n");
}

void asm_store(char *name){
	emit("\tMOV WORD PTR %s, AX\n",name);
}

void asm_not(){
	emit("\tNOT AX\n");
}

void asm_popand(){
	emit("\tPOP BX\n");
	emit("\tAND AX, BX\n");
}

void asm_popor(){
	emit("\tPOP BX\n");
	emit("\tOR AX, BX\n");	
}

void asm_popxor(){
	emit("\tPOP BX\n");
	emit("\tXOR AX, BX\n");
}

void asm_popcompare(){
	emit("\tPOP BX\n");
	emit("\tCMP BX, AX\n");	
}

void asm_relop(char op, int l1,int l2){
	char *jump;
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
	emit("\t%S L%d\n",jump,l1);
	emit("\tXOR AX, AX\n");
	emit("\tJMP L%d\n",l2);
	emit("L%d:\n",l1);
	emit("\tMOV AX, -1\n");
	emit("L%d:\n",l2);
}

void asm_jmp(int label){
	emit("\tJMP L%d\n", label);
}

void asm_jmpfalse(int label){
	emit("\tJZ L%d\n", label);
}

void asm_read(char *value){
	emit("\tCALl READ\n");
	asm_store(value);
}

void asm_write(){
	emit("\tCALL WRITE\n");
}

void allocVar(char *name, int value){
	emit("%s:\tDW %d\n",name,value);
}