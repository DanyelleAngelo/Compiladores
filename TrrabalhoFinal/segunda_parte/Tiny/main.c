#include <string.h>
#include <stdio.h>
#include "tiny.h"


int main(){
	init();
	topDecls();
	match('B');
	newLine();
	doBlock();

	dumpTable();
	return 0;
}