#ifndef INTERPRETER_H
#define INTERPRETER_H

#define MAX_NAME 20
#define MAX_NUM 30
#define MAXVAR 26
char lookahead;
int *var;

/*
*@brief inicia o compilador
*/
void init();

/*
*@brief aloca espaço e inicializa a matriz que guardará nossas variáveis
*/
void initVar();

/*
*@brief lê caractere
*/
void nextChar();

/*
*@brief lê  o próximo caractere sempre que encontra uma quebra de linha (remove as quebras de linha da nossa análise)
*/
void newLine();

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
int getNum();

/*
*@brief exibe uma instrução
*/
void emit(char *fmt, ...);

/* 
* @brief reconhece e traduz uma expressão 
*/
int expression();

/*
*@brief reconhece e traduz um termo
*/
int term();

/*
*@brief reconhece um termo de uma expressão e salva o mesmo no registrador AX
*/
int factor();

/*
*@brief lê um caractere, verifica se o caractere seguinte é o sinal de atribuição, em caso positivo traduz a expressão.
*/
void assignment();

/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de divisão ou multiplicação
*/
int isMulOp(char c);

/*
*@brief interpreta um comando de entrada
*/
void input();

/* 
*@brief interpreta um comando de saída
*/
void output();
#endif