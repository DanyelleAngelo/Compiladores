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

/* 
* @brief reconhece e traduz uma expressão 
*/
void expression();

/*
*@brief reconhece e traduz um termo
*/
void term();

/*
*@brief reconhece um termo de uma expressão e salva o mesmo no registrador AX
*/
void factor();

/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/* 
* @brief reconhece operação de multiplicação e traduz pra assembly a expressão
*/
void multiply();

/* 
* @brief reconhece operação de divisão e traduz pra assembly a expressão analisada
*/
void divide();

/* 
* @brief reconhece operação de adição e traduz pra assembly a expressão usando o operador ADD
*/
void add();

/* 
* @brief reconhece operação de subtração e traduz pra assembly a expressão usando o operador SUB
*/
void subtract();
#endif