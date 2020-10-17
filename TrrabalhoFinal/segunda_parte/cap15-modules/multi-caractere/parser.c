#include <ctype.h>
#include "parser.h"
#include "scanner.h"
#include "../input.h"
#include "../errors.h"
#include "../codegen.h"

void factor(){
	char name[MAX_NAME+1],num[MAX_NUM+1];
	if(isalpha(lookahead)){
		getName(name);
		asmLoadVariable(name);
	}else if(isdigit(lookahead)){
		getNum(num);
		asmLoadConstant(num);
	}else error("Unrecognized character: '%c'", lookahead);
}