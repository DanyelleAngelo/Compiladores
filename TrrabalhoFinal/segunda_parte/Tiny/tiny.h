#ifndef TINY_H
#define TINY_H

#define SYMTBL_SZ 26
#define PARAMS_SZ 26

char lookahead,symTbl[SYMTBL_SZ];

/*
*@brief gera código para armazenamento de variável
*/
void asm_allocvar(char name, char type);

/*
*@brief traduz o  código para carregar uma variável de acordo com o seu tipo
*/
void asm_loadvar(char  name,char type);

/*
*@brief traduz o  código para carregar uma constante de acordo com o seu tipo
*/
void asm_loadconst(long num, char type);

/*
*@brief traduz  código para armazenamento de acordo com o tipo da variável
*/
void asm_storevar(char name,char type);

/*
*@brief converte de um tipo para outro
*/
void asm_convert(char src,char dst);

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
*@brief avisa a respeito de um identificador que nã é variável
*/
void notVar(char  name);

/*
*@brief imprime tabela de símbolos
*/
void dumpTable();

/*
*@brief retorna o "tipo" de um identificador
*/
char symType(char name);

/*
*@brief verifica se uma variável já foi declarada
*/
char inTable(char name);

/*
*@brief verifica se um identificador já foi declarado
*/
void checkedUp(char name);

/*
*@brief chama checkedUp para verificar se a variável já foi declarada, 
*se não tiver sido adiciona o tipo da variável na tabela de símbolos na posição referente a variável
*/
void addSymbol(char name, char type);

/*
*@brief verifica se a entrada dá match com o esperado, chamand expected c.c.
*/
void match(char c);

/*
*@brief verifca se o nome de um indetificador ou palavra-chave é formado por letras
*vai salvando cada caractere formador do identificador
*/
char getName();

/*
*@brief verifica se lookahead é um número, vai salvando cada digito do número e depois de
*formad retorna o número.
*/
long getNum();

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
*@brief reconhece um tipo válido de variável
*/
int isVarType(char c);

/*
*@brief chama procediment para pegar tipo da variável com base no nome
*e depois chama a rotina de aviso caso o tipo não seja válido
*@return tipo da variável 
*/
char varType(char name);

/*
*@brief verifica tipo da variável e chama procedimento para carregar variável de acordo com seu tipo
*@return tipo da variável
*/
char loadVar(char name);

/*
*@brief define um tipo para uma constante numérica e a carrega no registrador primário
*@return tipo da constante
*/
char loadNum(long num);

/*
*@brief chama procedimento para armazenar variável de acordo com seu tipo
*/
void storeVar(char name,char srcType);

/* 
*@brief chama a rotina para inserir uma variável na tabela de símbolos e 
*depois a de alocação de memória
*/
void alloc(char name, char type);

/*
*@brief  analiza e traduz a declaração de uma variável.
*/
void decl();

/*
*@brief analiza e traduz declaraçẽs globais
*/
void topDecls();

/*
*@brief analisa e traduz uma expressão matemática
*@return tipo da variável carregada
*/
char expression();

/*
*@brief analisa e traduz um comando de atribuição
*associado a uma variavel
*/
void assignment();

/*
*@brief analisa e traduz um blocode comandos
*/
void doBlock();


#endif