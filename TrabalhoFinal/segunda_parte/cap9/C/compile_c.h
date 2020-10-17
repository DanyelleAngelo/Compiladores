#ifndef COMPILEC_H
#define COMPILEC_H

int lookahead;
char cur_class;
char cur_type;
char cur_sign;

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
*@brief analisa um programa Snall C
*/
void prog();

void preProc();

void intDecl();

void charDecl();

void doFunction(char name);

/*
*@brief analisa a classe de armazenamento, guarda ela em cur_class
*/
void getClass();

/*
*@brief analisa a definição de um tipo e armazena em cur_type
*/
void getType();

void topDecl();

void doData(char name);
#endif