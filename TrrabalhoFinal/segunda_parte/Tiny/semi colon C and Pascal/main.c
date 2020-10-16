#include <string.h>
#include <stdio.h>
#include "tiny.h"


int main(){
	init();
	matchString("PROGRAM");
	semiColon();
	header();
	topDecls();
	matchString("BEGIN");
	prolog();
	block();
	matchString("END");
	epilog();
	return 0;
}