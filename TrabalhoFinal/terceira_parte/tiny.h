#ifndef TINY_H
#define TINY_H

#define MAX_TOKEN 16
#define KWLIST_SZ 9
#define SYMTBL_SZ 1000


char lookahead,token, *symTbl[SYMTBL_SZ], symType[SYMTBL_SZ],value[MAX_TOKEN+1];
int nSym, labelCount; 

void nextChar_x();
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
void asm_loadconst(char *val);

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
*@brief lê próximo caractere
*/
void nextChar();

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
*@brief verifica se a entrada dá match com o esperado, chamando expected c.c.
*/
void matchString(char *s);

/*
*@brief verifica se uma palavra "s" pertence a uma lista "list"
*/
int lookaheadUp(char *s, char *list[], int size);

/*
*@brief retorna o endereço do identificador na tabela de símbolo
*/
int locate(char *name);

/*
*@brief verifica se o token corrente faz referencia a uma keyword 
*se token == 'x' então value é uma string, essa string é então passada
*para lookaheadup que faz a comparação da string com cada keyword da nossa lista
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
*@brief reconhece com que tipo de token estamos lidando
*/
void nextToken();


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
*@brief exibe uma mensagem  de erro dizend qe se esperava receber o nome de um identificador
*/
void checkIdent();

/*
*@brief exibe uma mensagem  de erro relativa a uma multideclaração 
*/
void  duplicated(char *name);

/*
*@brief verifica chamando a função looakheadUp se uma variável existe na nossa tabela de símbolos 
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
void addSymbol(char *name,char type);

/*
*@brief inicializa e aloca memória para uma declaração de variável
*/
void allocVar(char *name, int value);

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

/*
*@brief analisa e traduz um bloco de comandos
*/
void block();

/*
*@brief analisa e traduz um termo
*/
void term();

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
*@brief reconhece uma lista de parâmetros (separados por vírgulas)
*/
void doRead();

/*
*@brief
*/
void doWrite();

#endif