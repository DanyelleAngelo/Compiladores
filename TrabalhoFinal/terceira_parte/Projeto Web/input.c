#include <stdio.h>
#include "input.h"
#include "output.h"
#include "list.h"
#include "scanner.h"
#include "parser.h"
#include "parser.h"
#include "errors.h"

void init(){
	cursor =0;
	printf("%s\n",textoGrande);
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
	lookahead = textoGrande[cursor++];
}
