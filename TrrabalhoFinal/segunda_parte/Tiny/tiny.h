#ifndef TINY_H
#define TINY_H

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
*@return inteiro lido do código fonte
*/
int getNum();

/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de multiplicação ou divisão
*/
int isMulOp(char c);

/*
*@brief aloca espaço na memória para uma variável name e inicializa a mesma com getNum
*caso o lookahead atual for "="
*/
void allocVar(char name);

/*
*@brief reconhece os limitadores do programa de entrada escrito em Tiny
*/
void prog();

/*
*@brief emite o código inicial necessário para o montador
*/
void header();

/*
*@brief verifica os tipos de declaração do código de entrada e desvia o fluxo do compilador
*para os procedimento dos respectivos tipos detectados.
*/
void topDecls();

/*
*/
void decl();

/*
*@brief verifica o bloco principal
*/
void mainBlock();

/*
*@brief emite o código que identifica o programa principal para retornar ao sistema operacional
*/
void prolog();

/*
*@brief emite o código que identifica o programa principal para a inicialização
*/
void epilog();

#endif