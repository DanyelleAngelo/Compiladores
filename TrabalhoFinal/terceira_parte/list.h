/*Danyelle Angelo*/
#ifndef LIST_H
#define LIST_H

#include<stdlib.h>

typedef void* (*fn_constructor)(void*);
typedef void (*fn_destructor)(void*);

/*
*@brief elemento da lista, com um atributo data para guardar os dados e um next para apontar para o no que o sucede
*/
typedef struct listNode{
	void *data;
	struct  listNode *next;
}listNode;

/*
*@brief estrutura dalista, com ponteiro para o primeiro e último elemento da lista (head e tail),funções para alocação
*e liberação deespaço na memória dos nós da lista (constructor e destructor).e tamanho da lista
*/
typedef struct  list_t{
	listNode *head;
	listNode *tail;
	fn_constructor constructor;
	fn_destructor destructor;
	size_t size;
}list_t;

/*
*@brief poteiro para iterar sobre os nós da lista "embelezamento-sintático"
*/
typedef listNode *listIterator;

/*
*@brief inicializa a lista.
*@param list: dado definido pelo utilizador, o espaço para lista é alocado usando esse parametro
*@param constructor: função definda pelo utilizador, reponsável por alocar espaço para o elemento a ser inserido
*@param destructor: função definda pelo utilizador, reponsável por liberar espaço de um elemento
*/
void listInitialize(list_t **list,fn_constructor constructor,fn_destructor destructor);

/*
*@brief cria um novo elemento para a lista e atribui  como seu sucessor NULL
*@param data: elemento a ser inserido na lista
*@param constructor: função definda pelo utilizador, reponsável por alocar espaço para o elemento a ser inserido
*@return nó inicializado 
*/
listNode * newListNode(void *data,fn_constructor constructor);

/*
*@brief libera o espaço na memória usado para alocar o element inserido na lista (usando destructor) e depois libera o espaço ocupado por node
*@param node: elemento a ser deletado lista
*@param destructor: função definda pelo utilizador, reponsável por liberar o espaço para o elemento inserido
*/
void deleteNode(listNode *node,fn_destructor destructor);

/*
*@brief remove o head da lista 3nquanto size for diferente de 0 (enquanto ela não estiver vazia)
*@param list: lista de nós
*/
void listDelete(list_t **list);

/*
*@brief retorna o primeiro elemento da lista list->head
*@param list: lista
*@return head->data (sendo que data é o elemento passado no momento de inserção)
*/
void *listAccessHead(list_t *list);

/*
*@brief retorna o último elemento da lista list->tail
*@param list: lista
*@return tail->data (sendo que data é o elemento passado no momento de inserção)
*/
void *listAccessTail(list_t *list);

/*
*@brief retorna um elemento da lista com posição = pos 
*@param list: lista
*@param pos: elemento a ser retornado
*@return node->data (sendo que data é o elemento passado no momento de inserção)
*/
void *listAccess(list_t *list, size_t pos);

/*
*@brief remove o primeiro elemento da lista list->head
*@param list: lista
*/
void listRemoveHead(list_t *list);

/*
*@brief remove o último elemento da lista list->tail
*@param list: lista
*/
void listRemoveTail(list_t *list);

/*
*@brief remove um elemento da lista com posição = pos 
*@param list: lista
*@param pos: elemento a ser removido
*/
void listRemove(list_t *list,size_t pos);

/*
*@brief insere um elemento no inicio da lista
*@param list: lista
*@param data: elemento a ser inserido
*/
void listPrepend(list_t *list, void *data);

/*
*@brief insere um elemento no fim da lista
*@param list: lista
*@param data: elemento a ser inserido
*/
void listAppend(list_t *list,void *data);

/*
*@brief insere um elemento em uma posição = pos da lista
*@param list: lista
*@param data: elemento a ser inserido
*@param pos: local da lista onde data deve ser inserido
*/
void listInsert(list_t *list, void *data, size_t pos);

/*
*@brief verifica o tamanho da lista
*@param list: lista a qual desejo saber o tamanho
*@return tamanho da lista
*/
size_t listSize(list_t *list);

/*
*@brief  verifica se a lista está vazia
*@param list:lista
*@return 0  se a lista estiver vazia e 1 caso contrário
*/
size_t listEmpty(list_t *list);

#endif