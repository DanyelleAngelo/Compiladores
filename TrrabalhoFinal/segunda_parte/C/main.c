#include <string.h>
#include <stdio.h>
#include "compile_c.h"


int main(){
	init();
	while(lookahead != EOF){
		getClass();
		getType();
		topDecl();
	}
	return 0;
}