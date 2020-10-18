#include <string.h>
#include <stdio.h>
#include "input.h"
#include "parser.h"
#include "scanner.h"
#include "output.h"


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