#ifndef CRADLE_H
#define CRADLE_H

char lookahead;


/*
*@brief inicia o compilador
*/
void init();

/*
*@brief lê caractere
*/
void nextChar();

/*
*@brief mostra uma mensagem de erro com formatação
*/
void error(char *s);

/*
*@brief mostra uma mensagem de erro e encerra o programa
*/
void fatal(char *s);

/*
*@brief chamada para exibir mensagem sobre uma entrada esperada 
*/
void expected(char *s);

/*
*@brief verifica se a entrada dá match com o esperado, chamand expected c.c.
*/
void match(char c);


/*
*@brief verifca se o nome de um indetificador é formado por letras
*/
char getName();

/*
*@brief verifica se lookhead é um número
*/
char getNum();

/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de multiplicação ou divisão
*/
int isMulOp(char c);

#endif