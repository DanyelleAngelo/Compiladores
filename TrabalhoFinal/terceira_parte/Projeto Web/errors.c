#include <stdio.h>
#include<stdlib.h>
#include "output.h"
#include "errors.h"

void error(char *s){
	emit("<span class='error'>Error: %s</span><br>\n", s);
}

void fatal(char *s){
	error(s);
	exit(1);
}

void expected(char *s){
	emit("<span class='error'>Error: %s expected</span><br>\n",s);
	exit(1);
}

void undefined(char *name){
	emit("<span class='error'>Error: Undefinied identifier %s</span><br>\n",name);
	exit(1);
}

void  duplicated(char *name){
	emit("<span class='error'>Duplicated variable name: %s</span><br>\n",name );
	exit(1);
}