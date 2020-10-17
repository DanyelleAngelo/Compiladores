#include "output.h"
#include "codegen.h"

void asmLoadConstant(char *s){
	emit("MOV AX, %s",s);
}

void asmLoadVariable(char *s){
	emit("MOV AX, [%s]",s);	
}