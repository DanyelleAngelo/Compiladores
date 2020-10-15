#ifndef TINY_H
#define TINY_H

#define VAR_TBL_SZ 26
char lookahead;
int *varTbl, labelCount; 

/* 
*@brief zera o registrador primário
*/
void asm_clear();

/* 
*@brief negativa o registrador primário
*/
void asm_negative();

/* 
*@brief carrega uma constante numérica no registrador primário
*/
void asm_loadconst(int i);

/* 
*@brief carrega uma variável no registrador primário
*/
void asm_loadvar(char name);

/*
*@brief coloca registrador primário na pilha
*/
void asm_push();

/*
*@brief adiciona o topo da pilha ao registrador primário
*/
void asm_popadd();

/*
*@brief subtrai o registrador primário do topo da pilha
*/
void asm_popsub();

/*
*@brief multiplica o topo da pilha pelo registrador primário
*/
void asm_popmul();

/*
*@brief divide o topo da pilha pelo registrador primário
*/
void asm_popdiv();

/*
*@brief armazena registrador primário em variável
*/
void asm_store(char name);

/*
*@brief inverte registrador primário
*/
void asm_not();

/*
*@brief cálculo de "E" do topo da pilha com registrador primário
*/
void asm_popand();

/*
*@brief cálculo de "OU" do topo da pilha com registrador primário
*/
void asm_popor();

/*
*@brief cálculo de "OU-exclusivo" com o topo da pilha com registrador primário
*/
void asm_popxor();

/*
*@brief compara o topo da pilha com registrador primário
*/
void asm_popcompare();

/*
*@brief altera registrador primário (e flags, indiretamente) conforme a comparação
*/
void asm_relop(char op);

/*
*@brief desvio incondicional
*/
void asm_jmp(int label);

/*
*@brief desvio se falso (0)
*/
void asm_jmpfalse(int label);

/*
*@brief lê um valor para o registrador primário e armazena em variável
*/
void asm_read();

/*
*@brief mostra valor do registrador primário
*/
void asm_write();

/*
*@brief inicia o compilador lendo o primeiro símbolo do programa de entrada
*aloca espaço e inicializa a tabela de símbolos com 0
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
*@brief cria um rótulo
*/
int newLabel();

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
*@brief reconhece um operador OU
*/
int isOrOp(char c);

/*
*@brief reconhece operadores relacionais.
*/
int isRelOp(char c);

/*
*@brief verifica se uma ariável existe na nossa tabela de símbolos
*/
int intable(char name);

/*
*@brief exibe uma mensagem  de erro relativa a referência a um identificador não declarado e
*encerra a compilação
*/
void undefined(char name);

/*
*@brief verifica se a declaração analisada existe na tabela de símbolos, se existir retorna
*uma mensagem de erro, c.c marca a variável na tabela de simbolos como declarada e aloca 
*espaço na memória para a mesma
*/
void allocVar(char name);

/*
*@brief verifica os tipos de declaração do código de entrada e desvia o fluxo do compilador
*para os procedimento dos respectivos tipos detectados.
*/
void topDecls();

/*
*@brief verifica a declaração de uma ou mais variáveis
*/
void decl();

/*
*@brief
*/
void block();

/*
*@brief analisa e traduz um termo
*/
void term1();

/*
*@brief dispara as rotina para reconhecer e traduzir um termo
*/
void term();

/*
*@brief analisa e traduz um termo inicial
*/
void firstTerm();

/*
*@brief analisa e traduz uma expressão matemática
*/
void expression();

/*
*@brief analisa (é constante,variável ou '('??) e traduz um fator matemático
*/
void factor();

/*
*@brief analisa e traduz um fator negativo
*/
void negFactor();

/*
*@brief analisa e traduz um fator inicial
*/
void firstFactor();

/*
*@brief analisa e traduz um cmando de atribuição
*/
void assignment();

/*
*@brief analisa e traduz uma relação
*/
void relation();

/*
*@brief analisa e traduz um fator booleano com NOT inicial
*/
void notFactor();

/*
*@brief analisa e traduz um termo booleano
*/
void boolTerm();

/*
*@brief analisa e traduz uma expressão booleana
*/
void boolExpression();

/*
*@brief reconhece e traduz um "OR"
*/
void boolOr();

/*
*@brief reconhece e traduz um "xor"
*/
void boolXor();

/*
*@brief reconhece e dispara a rotina que traduz adição
*/
void add();

/*
*@brief reconhece e dispara a rotina que traduz subtração
*/
void subtract();

/*
*@brief reconhece e traduz uma multiplicação
*/
void multiply();

/*
*@brief reconhece e traduz divisão
*/
void divide();

/*
*@brief reconhece e traduz a estrutura de controle if
*/
void doIf();

/*
*@brief reconhece e traduz a estrutura de controle while
*/
void doWhile();

/*
*@brief verifica o bloco principal
*/
void mainBlock();

/*
*@brief reconhece os limitadores do programa de entrada escrito em Tiny
*/
void prog();

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