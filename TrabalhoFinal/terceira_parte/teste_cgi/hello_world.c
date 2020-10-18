#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int charc, char *charv[]){
	long idade;
	char *data;
	data = getenv("QUERY_STRING");//pega conteúdo  enviado no form
	printf("Content-type:text/html\n\n");
	if(strcmp(data,"")==0){
		printf("<html><head><title>Ola</title></head>\n");
		printf("<body>");
		printf("<form method=get action=idade>\n");
		printf("Idade<br>");
		printf("<input type=text maxlength=3 size=5 name=idade>");
		printf("<input type=submit value='Continuar'>");
		printf("</form></body></html>");
	}else if(sscanf(data,"idade=%ld",&idade) != 1){
  		printf("Idade deve ser numerica");
	}else{
		printf("Idade %ld<br> proxima idade e %ld\n",idade,idade+1);
	}
	
  	return 0;
}