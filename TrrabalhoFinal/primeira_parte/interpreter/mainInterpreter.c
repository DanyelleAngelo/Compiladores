#include <stdio.h>
#include "interpreter.h"

int main(){
	init();
	do{
		switch(lookahead){
			case '!':
				output();
				break;
			case '?':
				input();
				break;
			default:
				assignment();
				break;
		}
		newLine();
	}while(lookahead != '.');

	return 0;
}