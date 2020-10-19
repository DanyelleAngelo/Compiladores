#ifndef PARSER_H 
#define PARSER_H 
#include "../manage/list.h"

int labelCount;

list_t * symbol;

typedef struct variable{
	char *name;
	char *type;
	char *value;
}Variable;


/*
*@brief cria um rótulo
*/
int newLabel();

/*
*@brief analisa e traduz um bloco de comandos
*/
void block();

/*
*@brief reconhece uma lista de parâmetros (separados por vírgulas)
*/
void doRead();

/*
*@brief
*/
void doWrite();


/*
*@brief analisa (é constante,variável ou '('??) e traduz um fator matemático
*/
void factor();

/*
*@brief analisa e traduz um fator booleano com NOT inicial
*/
void notFactor();

/*
*@brief analisa e traduz um termo
*/
void term();

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
*@brief reconhece e traduz a estrutura de controle if-else-endif
*/
void doIf();

/*
*@brief reconhece e traduz a estrutura de controle while-endwhile
*/
void doWhile();


/*
*@brief analisa e traduz um termo booleano
*/
void boolTerm();

/*
*@brief analisa e traduz uma expressão booleana
*/
void boolExpression();

/*
*@brief analisa e traduz uma relação de: diferente,menor ou igual, maior ou igual
*/
void relation();

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
*@brief aloca espaço para uma variável
*/
void * constructorVariable(void* data);

/*
*@brief llibera espaço da memória
*/
void destructorVariable(void* data);

/*
*@brief inicializa a struct com as informaçẽs da variável
*/
void initializeStruct(Variable * var,char *name, char *type,char *value);

/*
*@brief retorna o endereço do identificador na tabela de símbolo
*/
int locate(char *name);

/*
*@brief exibe uma mensagem  de erro dizendo qe se esperava receber o nome de um identificador
*/
void checkIdent();

/*
*@brief verifica se uma variável ja foi delcarada na nossa lista de variáveis 
*/
int intable(char *name);

/*
*@brief dispara undefined caso um símbolo seja referenciado mas nã exista na tabela de simbolos 
*/
void checkTable(char *name);

/*
*@brief dispara a rotina duplicated para avisar de uma multi-declaração, caso haja uma
*/
void checkedUp(char *name);

/*
*@brief chama checkedup para verificar se a variável já foi declarada, se sim encerra o programa;
*se não verifica se a tabela de símbolos não atingiu sua capacidade máxima, se sim encerra programa,
*se não aloca espaço na memória, se tudo der  certo salva o novo símbolo alocado na tabela de símbolos.
*/
void addSymbol(char *name,char *type);

/*
*@brief reconhece declarações de variáveis em uma ou mais linhas
*/
void topDecls();

/*
*@brief verifica a declaração variável e chama as rotinas de adição na tabela de símbolos e alocação de espaço
*/
void decl();

/*
*@brief reconhece um identificador
*/
void readVar();


#endif