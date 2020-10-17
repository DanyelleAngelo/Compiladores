#ifndef CODEGEN_H
#define	CODEGEN_H

/*
*@brief gera um código assembly para carregar uma constante no registrador primário
*/
void asmLoadConstant(char *s);

/*
*@brief traduz o  código para carregar uma variável no registrador primário
*/
void asmLoadVariable(char *s);

#endif