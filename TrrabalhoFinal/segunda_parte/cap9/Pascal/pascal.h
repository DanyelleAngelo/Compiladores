#ifndef PASCAL_H
#define PASCAL_H

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

/*
*@brief analisa e traduz um programa
*/
void prog();

void prolog();

void epilog(char name);

/*
*@brief processa um bloco
*/
void doBlock(char name);

/*
*@brief verifica tipo
*/
void declaration();

/*
*@brief verifica e reconhece um comando 
*/
void statements();

/*
*@brief reconhece e traduz a declaração de uma label
*/
void labels();

/*
*@brief reconhece e traduz a declaração de uma constante
*/
void constants();

/*
*@brief reconhece e traduz a declaração de um type
*/
void types();

/*
*@brief reconhece e traduz a declaração de uma variável
*/
void variables();

/*
*@brief reconhece e traduz a declaração de uma procedure
*/
void doProcedure();

/*
*@brief reconhece e traduz a declaração de uma função
*/
void doFunction();
#endif