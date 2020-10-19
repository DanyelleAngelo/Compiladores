#include <stdio.h>
#include "input.h"
#include "../view/output.h"
#include "list.h"
#include "../controller/scanner.h"
#include "../controller/parser.h"
#include "../view/errors.h"

void init(){
	listInitialize(&symbol,constructorVariable,destructorVariable);
	labelCount = 0;
	nextChar();
	nextToken();
	matchString("PROGRAM");
	semiColon();
	header();
	topDecls();
	matchString("BEGIN");
	prolog();
	block();
	matchString("END");
	epilog();
}

void nextChar(){
	lookahead = getchar();
}
