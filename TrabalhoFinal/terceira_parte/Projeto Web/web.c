#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "parser.h"
#include "scanner.h"
#include "output.h"
#include "alloc.h"
#include "web.h"

void style(){
	printf("<style>");
	printf("*{margin:0 ; padding:0}");
	printf("#content{width:95%%;height:87%%;margin:0 auto;padding: 20px 0;}");
	printf("span.error{color:red;font-weight:bold}\n");
	printf("h4{text-align:center}");
	printf("button{margin:15px !important}");
	printf("</style>\n");
}

void formulario(){
	printf("<div  class='col-12 col-sm-6'>\n");
	printf("<form id='formulario' method=post action=codigoenctype='multipart/form-data'>\n");
	printf("<br><h4>Insira seu código Tiny aqui</h4><br>\n");
	printf("<input type='file' size='50' name='codigo' title='Clique para procurar arquivo' ><br><br>\n");
	printf("<div id='buttons'>\n");
	printf("<button type='submit' class='btn btn-primary btn-lg'>Compilar</button>\n");	
	printf("<button type='reset' class='btn btn-primary btn-lg'>Limpar tela</button>\n");	
	printf("</div>\n");					
	printf("</form>\n");
	printf("</div>\n");
}

void explanation(){
	printf("<div id='texto' class='col-12 col-sm-6'>\n");
	printf("Explicação\n");
	printf("</div>\n");
}

int main(int charc, char *charv[]){
	char *data,*codigo,*res;
	data = getenv("CONTENT_LENGTH");//pega conteúdo  enviado no form
	printf("Content-type:text/html\n\n");
	printf("<html><head><title>Tiny1.3.1</title></head>\n");
	printf("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css' integrity='sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin='anonymous'>\n");
	printf("<meta charset='utf-8'/>\n");
	style();
	printf("<body>\n");
	printf("<div id='content'>\n\n");		
	
	if(strcmp(data,"")==0){
		printf("<div class='row'>\n");
		formulario();
		explanation();
		printf("</div>\n");
	}else{
		sscanf(data,"%s",codigo);
		printf("%s\n", data);	
		textoGrande = myMalloc(sizeof(char)*(strlen(data)+1));
		strcpy(textoGrande,&data[7]);
		init();
	}
	printf("</div>\n\n");
	printf("</body></html>\n");
  	return 0;
}