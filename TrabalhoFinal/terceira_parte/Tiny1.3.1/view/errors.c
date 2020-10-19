#include <stdio.h>
#include<stdlib.h>
#include "output.h"
#include "errors.h"

void error(char *s){
	emit("Error: %s\n", s);
}

void fatal(char *s){
	error(s);
	exit(1);
}

void expected(char *s){
	emit("Error: %s expected\n",s);
	exit(1);
}

void undefined(char *name){
	emit("Error: Undefinied identifier %s\n",name);
	exit(1);
}

void  duplicated(char *name){
	emit("Duplicated variable name: %s\n",name );
	exit(1);
}