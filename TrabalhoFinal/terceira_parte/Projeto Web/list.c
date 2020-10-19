/*Danyelle Angelo*/
#include "list.h"
#include <stdlib.h>
#include <stdio.h>

void listInitialize(list_t **list,fn_constructor constructor,fn_destructor destructor){
	(*list)=malloc(sizeof(list_t));
	(*list)->head=NULL;
	(*list)->tail=NULL;
	(*list)->constructor=constructor;
	(*list)->destructor=destructor;
	(*list)->size=0;
}
listNode * newListNode(void *data,fn_constructor constructor){
	listNode *newNode = malloc(sizeof(listNode));
	newNode->data=constructor(data);
	newNode->next=NULL;
	return newNode;
}
void deleteNode(listNode *node,fn_destructor destructor){
	destructor(node->data);
	free(node);
}
void listDelete(list_t **list){
	while(listEmpty(*list)!=0){
		listRemoveHead(*list);
	}
}
void *listAccessHead(list_t *list){
	return list->head->data;
}
void *listAccessTail(list_t *list){
	return list->tail->data;
}
void *listAccess(list_t *list, size_t pos){
	if(listSize(list)==0 || pos==0){
		return listAccessHead(list);
	}
	else if(pos==listSize(list)-1){
		return listAccessTail(list);
	}
	else{
		listIterator aux=list->head;
		int i;
		for(i=0;i<pos;i++){
			aux=aux->next;
		}
		return aux;
	}
}
void listRemoveHead(list_t *list){
	listIterator node = list->head;
	list->head=node->next;
	if(listSize(list)==1){
		list->tail=NULL;
	}
	deleteNode(node,list->destructor);
	list->size--;
}
void listRemoveTail(list_t *list){
	listIterator node = list->head;
	if(listSize(list)==1){
		list->head=NULL;
		list->tail=NULL;
	}else{
		while(node->next!=list->tail){
			node=node->next;
		}
		listIterator aux = node->next;
		list->tail = node;
		list->tail=NULL;
		node=aux;
	}
	deleteNode(node,list->destructor);
	list->size--;
}
void listRemove(list_t *list,size_t pos){
	if(listSize(list)==1 || pos==0){
		listRemoveHead(list);
	}
	else if(pos==listSize(list)-1){
		listRemoveTail(list);
	}
	else{
		listIterator node=list->head;
		int i;
		for(i=0;i<pos-1;i++){
			node=node->next;
		}
		listIterator aux=node->next;
		node->next=aux->next;
		deleteNode(aux,list->destructor);
		list->size--;
	}
}
void listPrepend(list_t *list, void *data){
	listNode *newNode=newListNode(data,list->constructor);
	newNode->next=list->head;
	if(listEmpty(list)==0){
		list->tail=newNode;
	}
	list->head=newNode;
	list->size++;
}
void listAppend(list_t *list,void *data){
	listNode *newNode=newListNode(data,list->constructor);
	if(listEmpty(list)==0){
		list->head=newNode;
	}
	else{
		list->tail->next=newNode;
	}
	list->tail=newNode;
	list->size++;
}
void listInsert(list_t *list, void *data, size_t pos){
	if(listEmpty(list)==0 || pos==0){
		listPrepend(list,data);
	}
	else if(pos==(listSize(list)-1)){
		listAppend(list,data);
	}
	else{
		listNode *newNode = newListNode(data,list->constructor);
		listIterator aux=list->head;
		int i;
		for(i=0;i<pos-1;i++){
			aux=aux->next;
		}
		newNode->next=aux->next;
		aux->next=newNode;
		list->size++;
	}
}
size_t listSize(list_t *list){
	return list->size;
}
size_t listEmpty(list_t *list){
	return listSize(list)==0 ? 0:1;
}
