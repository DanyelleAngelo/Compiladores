/*
Juntando os analisadores: Primeiro passo - Sub-conjunto

O c�digo abaixo foi escrito por Felipo Soranz e � uma adapta��o
do c�digo original em Pascal escrito por Jack E. Crenshaw em sua
s�rie "Let's Build a Compiler".

Este c�digo � de livre distribui��o e uso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char look; /* O caracter lido "antecipadamente" (lookahead) */
int labelCount; /* indica o r�tulo atual */

/* prot�tipos */
void init();
void nextChar();
void error(char *fmt, ...);
void fatal(char *fmt, ...);
void expected(char *fmt, ...);
void match(char c);
char getName();
char getNum();
int isAddOp(char c);
int isMulOp(char c);
void skipWhite();
void newLine();
void emit(char *fmt, ...);

int newLabel();
int postLabel(int lbl);

void ident();
void factor();
void signedFactor();
void assignment();
void multiply();
void term1();
void firstTerm();
void term();
void add();
void subtract();
void expression();
void divide();
void condition();

void doIf();
void block();
void program();

/* PROGRAMA PRINCIPAL */
int main()
{
	init();
        program();

	return 0;
}

/* inicializa��o do compilador */
void init()
{
        labelCount = 0;
	nextChar();
	skipWhite();
}

/* l� pr�ximo caracter da entrada */
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
        skipWhite();
}

/* recebe o nome de um identificador */
char getName()
{
	char name;

        while (look == '\n')
                newLine();

	if (!isalpha(look))
		expected("Name");
	name = toupper(look);
	nextChar();
        skipWhite();

	return name;
}

/* recebe um n�mero inteiro */
char getNum()
{
	char num;

	if (!isdigit(look))
		expected("Integer");
	num = look;
	nextChar();
        skipWhite();

        return num;
}

/* reconhece operador aditivo */
int isAddOp(char c)
{
        return (c == '+' || c == '-');
}

/* reconhece operador aditivo multiplicativo */
int isMulOp(char c)
{
        return (c == '*' || c == '/');
}

/* ignora espa�os em branco e tabula��es */
void skipWhite()
{
	while (look == ' ' || look == '\t')
		nextChar();
}

/* ignora retorno de linha */
void newLine()
{
	if (look == '\n')
		nextChar();
}

/* emite uma instru��o seguida por uma nova linha */
void emit(char *fmt, ...)
{
	va_list args;

	putchar('\t');

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	putchar('\n');
}

/* gera um novo r�tulo �nico */
int newLabel()
{
	return labelCount++;
}

/* emite um r�tulo */
int postLabel(int lbl)
{
	printf("L%d:\n", lbl);
}

/* analisa e traduz um identificador */
void ident()
{
        char name;

        name = getName();
        if (look == '(') {
                match('(');
                match(')');
                emit("CALL %c", name);
        } else
                emit("MOV AX, [%c]", name);
}

/* analisa e traduz um fator */
void factor()
{

        if (look == '(') {
                match('(');
                expression();
                match(')');
        } else if(isalpha(look))
                ident();
        else
        	emit("MOV AX, %c", getNum());
}

/* analisa e traduz um fator com sinal */
void signedFactor()
{
        int s;

        s = (look == '-');
        if (isAddOp(look)) {
                nextChar();
                skipWhite();
        }
        factor();
        if (s)
                emit("NEG AX");
}

/* reconhece e traduz uma multiplica��o */
void multiply()
{
        match('*');
        factor();
      	emit("POP BX");
        emit("IMUL BX");
}

/* reconhece e traduz uma divis�o */
void divide()
{
        match('/');
        factor();
      	emit("POP BX");
        emit("XCHG AX, BX");
        emit("CWD");
        emit("IDIV BX");
}

/* analisa e traduz um termo (comum a firstTerm e term) */
void term1()
{
	while (isMulOp(look)) {
		emit("PUSH AX");
		switch(look) {
		  case '*':
		  	multiply();
		  	break;
		  case '/':
		  	divide();
		  	break;
		}
	}
}

/* analisa e traduz o primeiro termo */
void firstTerm()
{
        signedFactor();
        term1();
}

/* analisa e traduz um termo */
void term()
{
        factor();
        term1();
}

/* reconhece e traduz uma soma */
void add()
{
        match('+');
        term();
      	emit("POP BX");
        emit("ADD AX, BX");
}

/* reconhece e traduz uma subtra��o */
void subtract()
{
        match('-');
        term();
      	emit("POP BX");
        emit("SUB AX, BX");
        emit("NEG AX");
}

/* analisa e traduz uma express�o */
void expression()
{
       	firstTerm();
	while (isAddOp(look)) {
		emit("PUSH AX");
		switch(look) {
		  case '+':
		  	add();
		  	break;
		  case '-':
		  	subtract();
		  	break;
		}
	}
}

/* analisa e traduz um comando de atribui��o */
void assignment()
{
        char name;

	name = getName();
	match('=');
	expression();
	emit("MOV [%c], AX", name);
}



/* analisa e traduz uma condi��o */
void condition()
{
	emit("# condition");
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

/* analisa e traduz um bloco de comandos */
void block()
{
	int follow;

	follow = 0;

	while (!follow) {
		switch (look) {
		  case 'i':
		   	doIf(); break;
		  case 'e':
		  case 'l':
		   	follow = 1;
		   	break;
                  case '\n':
                        newLine();
                        break;
		  default:
		   	assignment(); break;
                }
	}
}

/* analisa e traduz um programa completo */
void program()
{
	block();
        match('e');
	emit("END");
}

