#ifndef ERRORS_H
#define ERRORS_H

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
*@brief exibe uma mensagem  de erro relativa a referência a um identificador não declarado e
*encerra a compilação
*/
void undefined(char *name);

/*
*@brief exibe uma mensagem  de erro relativa a uma multideclaração 
*/
void  duplicated(char *name);



#endif