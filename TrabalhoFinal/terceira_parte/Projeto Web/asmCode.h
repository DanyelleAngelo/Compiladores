#ifndef ASMCODE_H
#define ASMCODE_H

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
void asm_relop(char op, int l1,int l2);

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
void asm_read(char *vaue);

/*
*@brief mostra valor do registrador primário
*/
void asm_write();

/*
*@brief inicializa e aloca memória para uma declaração de variável
*/
void allocVar(char *name, int value);

#endif