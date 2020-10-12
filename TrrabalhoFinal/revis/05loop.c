/*
Estruturas de controle - LOOP

O código abaixo foi escrito por Felipo Soranz e é uma adaptação
do código original em Pascal escrito por Jack W. Crenshaw em sua
série "Let's Build a Compiler".

Este código é de livre distribuição e uso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char look; /* O caracter lido "antecipadamente" (lookahead) */
int labelCount; /* Contador usado pelo gerador de rótulos */

/* protótipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
void emit(char *fmt, ...);

int newLabel();
int postLabel(int lbl);

void other();
void doIf();
void doWhile();
void block();
void program();

/* PROGRAMA PRINCIPAL */
int main()
{
	init();
        program();

	return 0;
}

/* inicialização do compilador */
void init()
{
        labelCount = 0;
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

/* verifica se entrada combina com o esperado */
void match(char c)
{
	if (look != c)
		expected("'%c'", c);
	nextChar();
}

/* recebe o nome de um identificador */
char getName()
{
	char name;

	if (!isalpha(look))
		expected("Name");
	name = toupper(look);
	nextChar();

	return name;
}

/* recebe um número inteiro */
char getNum()
{
	char num;

	if (!isdigit(look))
		expected("Integer");
	num = look;
	nextChar();

	return num;
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

/* gera um novo rótulo único */
int newLabel()
{
	return labelCount++;
}

/* emite um rótulo */
int postLabel(int lbl)
{
	printf("L%d:\n", lbl);
}

/* analisa e traduz uma condição */
void condition()
{
	emit("# condition");
}

/* reconhece e traduz um comando qualquer */
void other()
{
        emit("# %c", getName());
}

/* analisa e traduz um comando IF */
void doIf()
{
	int l1, l2;

	match('i');
	condition();
	l1 = newLabel();
	l2 = l1;
	emit("JZ L%d", l1);
	block();
	if (look == 'l') {
		match('l');
		l2 = newLabel();
		emit("JMP L%d", l2);
		postLabel(l1);
		block();
	}
	match('e');
	postLabel(l2);
}

/* analisa e traduz um comando WHILE */
void doWhile()
{
	int l1, l2;

	match('w');
	l1 = newLabel();
	l2 = newLabel();
	postLabel(l1);
	condition();
	emit("JZ L%d", l2);
	block();
	match('e');
	emit("JMP L%d", l1);
	postLabel(l2);
}

/* analisa e traduz um comando LOOP */
void doLoop()
{
	int l;

	match('p');
	l = newLabel();
	postLabel(l);
	block();
	match('e');
	emit("JMP L%d", l);
}

/* analisa e traduz um bloco de comandos */
void block()
{
	while (look != 'e' && look != 'l') {
		switch (look) {
		  case 'i':
		   	doIf();
		   	break;
                  case 'w':
                        doWhile();
                        break;
                  case 'p':
                        doLoop();
                        break;
		  default:
		   	other();
		   	break;
		}
	}
}

/* analisa e traduz um programa completo */
void program()
{
	block();
	if (look != 'e')
		expected("End");
	emit("END");
}

