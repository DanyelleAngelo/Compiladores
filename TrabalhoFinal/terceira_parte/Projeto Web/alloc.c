#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"

void * myMalloc(size_t n){
	void * ptr = malloc (n);
	if(ptr==NULL){
		printf("Ocorreu um erro em my_malloc!\n<br>");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
void * myCalloc(size_t n,size_t s){
	void *ptr = calloc(n,s);
	if(ptr==NULL){
		printf("Ocorreu um erro em my_calloc!\n<br>");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
void * myRealloc(void *ptr,size_t n){
	void *aux = ptr = realloc(ptr,n);
	if(aux==NULL && n!=0){
		printf("Ocorreu um erro em my_realloc!\n<br>");
		exit(EXIT_FAILURE);
	}
	return aux;
}