#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void style(){
	printf("<style>");
	printf("*{margin:0 ; padding:0}");
	printf("#content{width:95%%;height:90%%;margin:0 auto}");
	printf("h4{text-align:center}");
	printf("button{margin:15px !important}");
	printf("</style>\n");
}

void formulario(){
	printf("<div id='formulario' class='col-12 col-sm-6'>\n");
	printf("<form method=get action=codigo>\n");
	printf("<br><h4>Insira seu código Tiny aqui</h4><br>\n");
	printf("<textarea name=codigo rows='19' style='width:95%%'></textarea><br><br>\n");
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
	char *data;
	data = getenv("QUERY_STRING");//pega conteúdo  enviado no form
	printf("Content-type:text/html\n\n");
	style();
	if(strcmp(data,"")==0){
		printf("<html><head><title>Tiny1.3.1</title></head>\n");
		printf("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css' integrity='sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm' crossorigin='anonymous'>\n");
		printf("<meta charset='utf-8'/>\n");
		printf("<body>\n");
		printf("<div id='content'>\n\n");
		printf("<div class='row'>\n");
		formulario();
		explanation();
		printf("</div>\n");
		printf("</div>\n\n");
		printf("</body></html>\n");
	}else{
		printf("<h2>Código Assembly</h2>\n");
	}
	
  	return 0;
}