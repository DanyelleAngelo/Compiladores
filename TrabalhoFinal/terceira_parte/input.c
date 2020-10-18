#include <stdio.h>
#include "input.h"
#include "output.h"
#include "list.h"
#include "scanner.h"
#include "parser.h"
#include "parser.h"
#include "errors.h"

void init(){
	listInitialize(&symbol,constructorVariable,destructorVariable);
	labelCount = 0;
	nextChar();
	nextToken();
}

void nextChar(){
	lookahead = getchar();
}
