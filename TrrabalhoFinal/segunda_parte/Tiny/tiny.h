#ifndef TINY_H
#define TINY_H

#define SYMTBL_SZ 1000


char lookahead,symTbl[SYMTBL_SZ];

void asm_allocvar(char name);

/* 
*@brief carrega uma variável no registrador primário
*/
void asm_loadvar(char name);

/*
*@brief armazena registrador primário em variável
*/
void asm_store(char name);

void asm_return();

/*
*@brief inicia o compilador lendo o primeiro símbolo do programa de entrada
*aloca espaço e inicializa a tabela de símbolos com 0
*/
void init();

/*
*@brief lê próximo caractere
*/
void nextChar();

/*
*@brief reconhece caractere de espaço em branco e delimitador inicial de cometário 
*e chama as rotinas correspondentes a cada caractere para avançar a posição do cursor de
*leitura
*/
void skipWhite();

/*
*@brief reconhece quebras de linhas: sempre que o analisadr encontrar um '\n'
*é pedid que o mesm leia o próximo caractere e que no processo reconheça todos
*os caracteres em branco.
*/
void newLine();

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
*@brief exibe uma mensagem sobre a referencia de um identificador
*não definid e encerra o programa 
*/
void undefined(char name);

/*
*@brief avisa sobre uma multideclaraçao de variável 
*/
void duplicated(char name);

/*
*@brief keyword não encontrada
*/
void unrecognized(char name);

/*
*@brief identificador não é do "tipo" variável
*/
void notVar(char name);

/*
*@brief retorna o "tipo" de um identificador
*/
char symType(char name);

/*
*@brief verifica se uma variável já foi declarada
*/
char inTable(char name);

/*
*@brief chama inTable para verificar se a variável já foi declarada, se sim chama duplicate para exibir
*mensagem e encerrar o programa;
*se não adiciona o tipo da variável na tabela de símbolos na posição referente a variável
*/
void addSymbol(char name, char type);

/* 
*@brief verifica se o identificador referenciado já foi declarado e seu tipo
*/
void checkVar(char name);

/*
*@brief verifica se a entrada dá match com o esperado, chamand expected c.c.
*/
void match(char c);

/*
*@brief verifca se o nome de um indetificador ou palavra-chave é formado por letras
*vai salvando cada caractere formador do identificador na variável global value 
*/
char getName();

/*
*@brief verifica se lookahead é um número, vai salvando cada digito do número na variável global value
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
*@brief reconhece um operador OU
*/
int isOrOp(char c);

/*
*@brief reconhece operadores relacionais.
*/
int isRelOp(char c);

/*
*@brief reconhece declarações de variáveis (em uma ou mais linhas)
*procedimento e do programa principal.
*/
void topDecls();

/*
*@brief verifica a declaração de uma variável e chama as rotinas de adição na tabela de símbolos e alocação 
*de espaço na memória
*/
void decl();

/*
*@brief analisa e traduz um bloco
*/
void doBlock();

/*
*@brief analisa e traduz uma declaração de procedimento
*/
void doProc();

/*
*@brief analisa e traduz um bloco begin
*/
void beginBlock();

/*
*@brief analisa e traduz uma expressão matemática
*/
void expression();

/*
*@brief analisa e traduz um comando de atribuição
*associado a uma variavel
*/
void assignment();

/*
*@brief analisa e traduz o blco principal do programa
*/
void doMain();

/*
*@brief emite o código inicial necessário para o montador
*/
void header();

/*
*@brief emite o código que identifica o programa principal para retornar ao sistema operacional
*/
void prolog();

/*
*@brief emite o código que identifica o programa principal para a inicialização
*/
void epilog();

#endif