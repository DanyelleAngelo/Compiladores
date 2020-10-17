#include <string.h>
#include <stdio.h>
#include "tiny.h"


int main(){
	init();
	prog();
	if(lookahead != '\n')fatal("Unexpected data after \'.\'");
	return 0;
}