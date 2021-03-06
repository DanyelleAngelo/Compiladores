#ifndef CRADLE_H
#define CRADLE_H

#define MAX_NAME 20
#define MAX_NUM 30
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
*@brief ignora os espaços em branco, enquanto enncontrar um caracter em branco chama a função nextChar() para ler um novo caractere.
*/
void skipWhite();

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
char getName(char *identifier);

/*
*@brief verifica se lookhead é um número
*/
char getNum(char *number);

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
*@brief verifica se o identificador analisado é a assinatura de uma função ou uma variável(ele faz isso lelndo o próximo caractere e verificando se ele é '(' ou não)
*/
void ident();

/*
*@brief lê um caractere, verifica se o caractere seguinte é o sinal de atribuição, em caso positivo traduz a expressão.
*/
void assignment();

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