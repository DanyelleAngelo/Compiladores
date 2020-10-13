#include <stdio.h>
#include "cradle.h"


int main(){
	init();
	do{
		scan();
		switch(token){
			case TK_IDENT:
				printf("Ident: ");
				break;
			case TK_NUMBER:
				printf("Number: ");
				break;
			case TK_OPERATOR:
				printf("Operator: ");
				break;
			case KW_IF:
			case KW_ELSE:
			case KW_ENDIF:
			case KW_END:
				printf("Keyword: ");
				break;
		}
		printf("%s\n",value);
		if(value[0] == '\n')newLine();
	}while(token!= KW_END);

	return 0;
}