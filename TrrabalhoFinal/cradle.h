#ifndef CRADLE_H
#define CRADLE_H

#define MAX_NAME 20
#define MAX_TOKEN 300
#define MAX_NUM 30
#define MAX_OP
#define SYMTBL_SZ 1000
#define KWLIST_SZ 4

char lookahead;
int labelCount; 
int token;
char value[MAX_TOKEN+1];

char *symtbl[SYMTBL_SZ];
char *kwlist[KWLIST_SZ] = {"IF", "ELSE", "ENDIF", "END"};
enum {KW_IF,KW_ELSE,KW_ENDIF,KW_END,TK_IDENT,TK_NUMBER, TK_OPERATOR };

/*
*@brief inicia o compilador
*/
void init();

/*
*@brief reconhece e traduz um comando qualquer
*/
void other();

/*
*@brief analisa e traduz o programa
*/
void programa();

/*
*@brief analisa, identifica o inicio/fim de umbloco  e o traduz 
*/
void block(int exitLabel);

/*
*@brief reconhece uma linha em branco
*/
void newLine();

/*
*@brief cria um rótulo
*/
int newLabel();

/*
*@brief emite o rótulo
*/
int postLabel(int lbl);

/*
*@brief verifica condicionais
*/
void condition();

/*
*@brief verifica relações
*/
void relation();

/*
*@brief analiza e traduz o comando de interrupção de laço.
*/
void doBreak(int exitLabel);

/*
*@brief trata do comando condicional if
*/
void doIf(int exitLabel);

/*
*@brief trata do comando de repetição while
*/
void doWhile();

/*
*@brief trata do comando de repetição loop, esse comando consiste em um laço de repetição infinito, 
*sendo similar a while(1)
*/
void doLoop();

/*
*@brief trata do comando de repetição REPEAT-UNTIL (advindo do Pascal)
*/
void doRepeat();

/*
*@brief implementa o comando for (aqui a sua sintaxe será similar a do Basic)
*/
void doFor();

/*
*@brief implementa laço Do, que tem o seu contador decrementado a cada iteração.
*/
void doDo();

void scan();

/*
*@brief lê caractere
*/
void nextChar();


/*
*@brief ignora os espaços em branco, enquanto enncontrar um caracter em branco chama a função nextChar() para ler um novo caractere.
*/
void skipWhite();


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
 

void getOp();

/*
*@brief verifca se o nome de um indetificador é formado por letras
*/
void getName();

/*
*@brief verifica se lookhead é um número
*/
void getNum();

/*
*@brief lê um boolean
*/
int getBoolean();

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
*@brief analisa um fator com sinal
*/
void signedFactor();

/*
*@brief verifica se o identificador analisado é a assinatura de uma função ou uma variável(ele faz isso lelndo o próximo caractere e verificando se ele é '(' ou não)
*/
void ident();

/*
*@brief lê um caractere, verifica se o caractere seguinte é o sinal de atribuição, em caso positivo traduz a expressão.
*/
void assignment();

int isOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de soma ou subtração
*/
int isAddOp(char c);

/*
*@brief verifica se o caractere analisado é um operador de multiplicação ou divisão
*/
int isMulOp(char c);

/* 
* @brief analisa e reconhece uma expressão booleana.
*/
void boolExpression();

/* 
* @brief analisa e traduz um fator booleano
*/
void boolFactor();

/*
*@brief analisa e traduz um termo booleano.
*/
void boolTerm();

/*
*@brief analisa operadores relacionais.
*/
int isRelOp(char c);

/*
*@brief  analisa e traduz um fator booleno com NOT opcional
*/
void noFactor();

/*
*@brief verifica se o operando é OR e traduz o mesmo
*/
void boolOr();

/*
*@brief verifica se o operando é XOR e traduz o mesmo
*/
void boolXor();

/*
*@brief reconhece um operador OU
*/
int isOrOp(char c);

/*
*@brief verifica se o token é do tipo boolean
*/
int isBoolean(char c);

/*
*@brief reconhece e traduz o operador de igualdade
*/
void equals();

/*
*@brief reconhece e traduz o operador diferente
*/
void notEquals();

/*
*@brief reconhece e traduz o operador maior que
*/
void greater();

/*
*@brief reconhece e traduz o operador menor que
*/
void less();

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