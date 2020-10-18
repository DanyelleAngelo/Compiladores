#ifndef SCANNER_H
#define SCANNER_H

#define MAX_NAME 20
#define MAX_NUM 26
/*
*@brief captura o nome de um identificador
*/
void getName(char *name);

/*
*@brief captura um número
*/
void getNum(char *num);

/*
*@brief verifica se a entrada dá match com o esperado, chamand expected c.c.
*/
void match(char c);


/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de multiplicação ou divisão
*/
int isMulOp(char c);

#endif