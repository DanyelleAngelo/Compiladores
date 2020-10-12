/*
Experiências

O código abaixo foi escrito por Felipo Soranz e é uma adaptação
do código original em Pascal escrito por Jack W. Crenshaw em sua
série "Let's Build a Compiler".

Este código é de livre distribuição e uso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXNAME  32
#define MAXNUM   5
#define MAXTOKEN 32

char look; /* O caracter lido "antecipadamente" (lookahead) */
char token[MAXTOKEN+1]; /* token atual da entrada */

/* protótipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
void getName(char *name);
void getNum(char *num);
void scan(char *token);
void emit(char *fmt, ...);

/* PROGRAMA PRINCIPAL */
int main()
{
	init();

        do {
                scan(token);
                printf("%s\n", token);
        } while (token[0] != '\n');

	return 0;
}

/* inicialização do compilador */
void init()
{
	nextChar();
}

/* lê próximo caracter da entrada */
void nextChar()
{
	look = getchar();
}

/* exibe uma mensagem de erro formatada */
void error(char *fmt, ...)
{
	va_list args;
	
	fputs("Error: ", stderr);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	
	fputc('\n', stderr);
}

/* exibe uma mensagem de erro formatada e sai */
void fatal(char *fmt, ...)
{
	va_list args;
	
	fputs("Error: ", stderr);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	
	fputc('\n', stderr);

	exit(1);
}

/* alerta sobre alguma entrada esperada */
void expected(char *fmt, ...)
{
	va_list args;
	
	fputs("Error: ", stderr);

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	
	fputs(" expected!\n", stderr);
	
	exit(1);
}

/* pula caracteres de espaço */
void skipWhite()
{
	while (look == ' ' || look == '\t')
		nextChar();
}

/* verifica se entrada combina com o esperado */
void match(char c)
{
	if (look != c)
		expected("'%c'", c);
	nextChar();
}

/* recebe o nome de um identificador */
void getName(char *name)
{
        int i;

	if (!isalpha(look))
		expected("Name");

	for (i = 0; isalnum(look); i++) {
		if (i >= MAXNAME)
			fatal("Identifier too long!");
		name[i] = toupper(look);
		nextChar();
	}
	name[i] = '\0';
}

/* recebe um número inteiro */
void getNum(char *num)
{
        int i;

	if (!isdigit(look))
		expected("Integer");

	for (i = 0; isdigit(look); i++) {
		if (i >= MAXNUM)
			fatal("Integer too long!");
		num[i] = look;
		nextChar();
	}
	num[i] = '\0';
}

/* Analisador Léxico */
void scan(char *token)
{
	if (isalpha(look))
		getName(token);
	else if (isdigit(look))
		getNum(token);
	else {
		token[0] = look;
		token[1] = '\0';
		nextChar();
	}
	skipWhite();
}

/* emite uma instrução seguida por uma nova linha */
void emit(char *fmt, ...)
{
	va_list args;
	
	putchar('\t');

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');
}

