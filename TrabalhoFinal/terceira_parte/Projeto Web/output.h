#ifndef OUTPUT_H
#define OUTPUT_H

/*
*@brief emite o código inicial necessário para o montador
*/
void header();

/*
*@brief emite o código que identifica o programa principal para retornar ao sistema operacional
*/
void prolog();

/*
*@brief emite o código que identifica o programa principal para a inicialização
*/
void epilog();

/*
*@brief exibe uma instrução
*/
void emit(char *s, ...);

#endif