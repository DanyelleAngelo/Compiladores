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
void error(char *fmt, ...);

/*
*@brief mostra uma mensagem de erro e encerra o programa
*/
void fatal(char *fmt, ...);

/*
*@brief chamada para exibir mensagem sobre uma entrada esperada 
*/
void expected(char *fmt, ...);

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
*@brief exibe uma instrução
*/
void emit(char *fmt, ...);

#endif