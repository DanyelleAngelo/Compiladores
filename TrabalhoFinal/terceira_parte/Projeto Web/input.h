#ifndef INPUT_H
#define INPUT_H

char *textoGrande;
int cursor;

/*
*@brief inicia o compilador lendo o primeiro símbolo do programa de entrada
*aloca espaço e inicializa a tabela de símbolos com 0
*/
void init();

/*
*@brief lê próximo caractere
*/
void nextChar();

#endif