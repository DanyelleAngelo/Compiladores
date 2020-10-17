#ifndef TINY_H
#define TINY_H

#define SYMTBL_SZ 26
#define PARAMS_SZ 26


char lookahead,symTbl[SYMTBL_SZ];
int params[PARAMS_SZ],nParams;

void asm_allocvar(char name);

/* 
*@brief carrega uma variável no registrador primário
*/
void asm_loadvar(char name);

/*
*@brief armazena registrador primário em variável
*/
void asm_store(char name);

/*
*@brief traduz retorno do procedimento
*/
void asm_return();

/*
*@brief calcula o deslocamento do parametro
*/
int asm_offsetpar(int par);

/*
*@brief traduz uma chamada de procedimento
*/
void asm_call(char name);

/*
*@brief carrega parametro em registrador primario
*/
void asm_loadparam(int par);

/*
*@brief "copia" valor de registrador primário para parametr
*/
void asm_storeparam(int par);

/*
*@brief coloca registrador primario na pilha
*/
void asm_push();

/*
*@brief ajusta o ponteiro da pilha acima
*/
void asm_cleanstack(int bytes);

/*
*@brief escreve o prólogo para um procedimento
*/
void asm_procprolog(char name);

/*
*@brief coloca parâmetros na pilha
*/
void asm_pushparam(char name);

/*
*@brief escreve o epílogo para um procedimento
*/
void asm_procepilog();

/*
*@brief inicia o compilador lendo o primeiro símbolo do programa de entrada
*aloca espaço e inicializa a tabela de símbolos com 0
*/
void init();

/*
*@brief reinicializa a lista de parametros formais a cada  procedimento
*/
void clearParams();

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
*@brief retorna a "classe" de um identificador
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
*@brief retorna um número indicando a posição do parametro 
*/
int paramNum(char name);

/*
*@brief verifica se name é um  parametro
*/
int isParam(char name);

/*
*@brief adiciona parametro a tabela de parametros
*/
void addParam(char name);

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
*@brief processa/adiciona na tabela de parametros um parametro formal(na declaração do procedimento eles são chamados assim)
*/
void formalParam();

/*
*@brief processa uma lista de parametros formais de um procedimento,
*a lista  pode ser vazia ou não, caso seja o último caso é chamada
*a rotina de análise de um parametro.
*/
void formalList();

/*
*@brief processa um parametro de chamada ("parametro verdadeiro")
*/
void param();

/*
*@brief processa uma lista de parametros verdadeiros
*@return números de bytes da pilha que devem ser limpos ao término do
*proedimeto
*/
int paramList();

/*
*@brief processa uma chamada de procedimento
*/
void doCallProc(char name);

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
void assignment(char name);

/*
*@brief analisa e traduz um comando de atribuição ou chamada
*de procedimento olhando o tipo do identificador na tabela de símbolos
*/
void assignOrCall();

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