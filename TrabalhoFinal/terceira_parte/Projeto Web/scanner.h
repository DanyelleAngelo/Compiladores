#ifndef SCANNER_H
#define SCANNER_H

#define MAX_TOKEN 16
#define KWLIST_SZ 9

char lookahead,token, value[MAX_TOKEN+1];
int labelCount;

/*
*@brief reconhece com que tipo de token estamos lidando
*/
void nextToken();

/*
*@brief trata de comentários simples e comentários aninhados: avança na leitura do próximo
*caractere até encontrar o delimitador final de umcomentário, se o próximo caractere for o 
*delimitador inicial de comentarios chama essa rotina recursivamente.
*/
void skipComment();

/*
*@brief reconhece caractere de espaço em branco e delimitador inicial de cometário 
*e chama as rotinas correspondentes a cada caractere para avançar a posição do cursor de
*leitura
*/
void skipWhite();

/*
*@brief sempre que encontra ponto-e-vírgula avança o cursor de leitura para o próximo token
*/
void semiColon();


/*
*@brief verifica se o token corrente faz referencia a uma keyword 
*/
void scan();

/*
*@brief verifca se o nome de um indetificador ou palavra-chave é formado por letras
*vai salvando cada caractere formador do identificador na variável global value 
*/
void getName();

/*
*@brief verifica se lookahead é um número, vai salvando cada digito do número na variável global value
*/
void getNum();

/*
*@brief verifica se lookahead é um operador  e o salva na variável global value
*/
void getOp();

/*
*@brief verifica se a entrada dá match com o esperado, chamando expected c.c.
*/
void matchString(char *s);

/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de multiplicação ou divisão
*/
int isMulOp(char c);

/*
*@brief reconhece um operador OU
*/
int isOrOp(char c);

/*
*@brief reconhece operadores relacionais.
*/
int isRelOp(char c);


#endif