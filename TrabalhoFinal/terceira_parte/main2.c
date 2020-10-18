#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alloc.h"
#include "list.h"

typedef struct aluno{
	char nome[40];
	char cpf[12];//somente números
	char curso[100];
	char matricula[14];
	int idade;
}Aluno;

void * constructor_pessoa(void* data){
    void* ptr = myMalloc(sizeof(Aluno));
    memcpy(ptr,data,sizeof(Aluno));//copia data (do tamanho de um inteiro) pra o bloco ptr
    return ptr;
}

void destructor_pessoa(void* data){
    free(data);
}
void le_pessoa(Aluno *a){
	printf("Nome = ");
	scanf("%s",a->nome);
	printf("Curso = ");
	scanf("%s",a->curso);
	printf("Matricula = ");
	scanf("%s",a->matricula);
	printf("CPF = ");
	scanf("%s",a->cpf);
	printf("Idade = ");
	scanf("%d",&(a->idade));
}
void imprime_pessoa(Aluno *a){
	printf("Nome = %s\n",a->nome);
	printf("Curso = %s\n",a->curso);
	printf("Matricula = %s\n",a->matricula);
	printf("CPF = %s\n",a->cpf);
	printf("Idade = %d\n",a->idade);
}
void iterator_pessoa(list_t  *l){
	int  i=0;
	printf("\n");
	listIterator aux = l->head;
	for(i=0;i<(l->size);i++){
		imprime_pessoa(aux->data);
		aux = aux->next;
		printf("\n");
	}
	printf("\n");
}
int main(void){
	list_t * l1;
	listInitialize(&l1,constructor_pessoa,destructor_pessoa);
	//le_pessoa(l1);
	int i;
	for(i=0;i<1;i++){
		Aluno a;
		printf("Aluno %d: \n",i+1);
		le_pessoa(&a);
		listInsert(l1,&a,i);
		printf("\n\n");
	}
	printf("Lista de alunos\n");
	iterator_pessoa(l1);
	listRemove(l1,0);
	printf("Lista de aluno apos remocao\n");
	iterator_pessoa(l1);
	return 0;
}
