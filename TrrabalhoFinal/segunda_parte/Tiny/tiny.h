#ifndef TINY_H
#define TINY_H

#define MAX_TOKEN 16
#define KWLIST_SZ 11
#define SYMTBL_SZ 1000


char lookahead, *symTbl[SYMTBL_SZ];
int nSym, labelCount; 
char token,value[MAX_TOKEN+1];


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
void asm_loadvar(char *name);

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
void asm_store(char *name);

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
*@brief reconhece caractere em branco e solicita a leitura do próximo
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
*@brief cria um rótulo
*/
int newLabel();

/*
*@brief verifica se a entrada dá match com o esperado, chamand expected c.c.
*/
void match(char c);

/*
*@brief verifica o match do token corrente com uma string fornecida como parametro.
*/
void matchString(char *s);

/*
*@brief verifica se uma palavra "s" pertence a uma lista "list"
*/
int lookaheadUp(char *s, char *list[], int size);

/*
*@brief verifica se o token corrente pertence a lista de palavras reservadas
*/
void scan();

/*
*@brief verifca se o nome de um indetificador é formado por letras
*/
void getName();

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
*@brief exibe uma mensagem  de erro relativa a referência a um identificador não declarado e
*encerra a compilação
*/
void undefined(char *name);

/*
*@brief verifica chamando a função looakheadUp se uma variável existe na nossa tabela de símbolos 
*/
int intable(char *name);


/*
*@brief chama intable para verificar se a variável já foi declarada, se sim encerra o programa;
*se não verifica se a tabela de símbolos não atingiu sua capacidade máxima, se sim encerra programa,
*se não aloca espaço na memória, se tudo der  certo salva o novo símbolo alocado e referencia espaço
*na tabela de símbolos.
*/
void addSymbol(char *name);

/*
*@brief chama addSymbol para adicionar o token lido na tabela de símbolos, veifica se o próximo token
*é um sinal de - e salva o token subsequente de acordo com o símbolo anterior (o próximo token é um número
*negativo?)
*/
void allocVar(char *name);

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
*@brief analisa e traduz um comando de atribuição
*associado a uma variavel
*/
void assignment();

/*
*@brief analisa e traduz uma relação de: diferente,menor ou igual, maior ou igual
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
*@brief reconhece e traduz a estrutura de controle if-else-endif
*/
void doIf();

/*
*@brief reconhece e traduz a estrutura de controle while-endwhile
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



/*criar uma biblioteca  a parte*/
/*
*@brief faz a leityra de uma lista de parâmetros (separados por vírgulas)
*/
void doRead();

/*
*@brief
*/
void doWrite();

#endif