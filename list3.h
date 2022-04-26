#ifndef __LISTA_H
#define __LISTA_H

#include <stdlib.h>
#include <stdint.h>

#include <stdio.h>
#include "util2.h"

typedef struct header header;

struct header{
	unsigned long int size;
	unsigned long int cap;
	unsigned long int data_size;
};

#define originalAdress(_list) _Generic((_list),		\
	int**:		((char**)_list - sizeof(header)),	\
	char**:		((char**)_list - sizeof(header)),	\
	float**:	((char**)_list - sizeof(header)),	\
	double**:	((char**)_list - sizeof(header)),	\
	void**:		((char**)_list - sizeof(header)),	\
	default: 	((char*)_list - sizeof(header))		\
)
	
#define headerAdress(_list) ((header*)originalAdress(_list))
#define getSize(_list) headerAdress(_list)->size
#define getCap(_list) headerAdress(_list)->cap
#define getDataSize(_list) headerAdress(_list)->data_size
#define isFull(_list) getSize(_list) >= getCap(_list)

#define createList(_list) _MakeList( _list, sizeof(*(_list)))

#define expandList(_list) _Generic((_list),					\
	int**:		_list =  _ExpandPointerList(_list),			\
	char**: 	_list =  _ExpandPointerList(_list),			\
	float**:	_list =  _ExpandPointerList(_list),			\
	double**:	_list =  _ExpandPointerList(_list),			\
	void**:		_list =  _ExpandPointerList(_list),			\
	default: 	_list =  _ExpandList(_list)					\
)

#define add(_list, _item) 							\
	if(isFull(_list)){								\
		expandList(_list);							\
	}												\
	_list[getSize(_list)] = _item;					\
	(getSize(_list))++;


void* _MakeList(void* list, unsigned long int data_size){
	list = malloc(sizeof(header) + 4 * sizeof(data_size));

	((header*)list)->data_size = data_size;
	((header*)list)->size = 0;
	((header*)list)->cap = 4;
	
	list+=sizeof(header);

	return list;
}

void** _MakePointerList(void**list , unsigned long int data_size){
	list = malloc(sizeof(header) + 4*sizeof(data_size));
	((header*)list)->data_size = data_size;
	((header*)list)->size = 0;
	((header*)list)->cap = 4;

	list+=sizeof(header);

	return list;;
}

void* _ExpandList(void* list){
	printf("Expand . . \n");
	void* aux = realloc(originalAdress(list),		\
		(2*getCap(list)*(getDataSize(list)))			\
		+sizeof(header));

	if(aux == NULL){
		printf("Falha ao expandir a lista\n");
		return list;
	}


	aux += sizeof(header);
	getCap(aux) *= 2;

	return aux;
}

void** _ExpandPointerList(void** list){
	list = realloc(originalAdress(list),			\
		(2*getCap(list)*(getDataSize(list)))		\
		+sizeof(header));

	list = list+sizeof(header);
	
	getCap(list) *= 2;

	return list;
}

int getListType(char* type){
	if(strEqual(type, "char")) return 1;
	if(strEqual(type, "int")) return 2;
	if(strEqual(type, "float")) return 3;
	if(strEqual(type, "double")) return 4;
	if(strEqual(type, "string")) return 5;
	if(strContains(type, "*")) return 6;

	return -1;
}

void* createListOf(char* type){
	void* list;
	int opt = getListType(type);
	switch(opt){
		case 1:
			list = _MakeList(list, sizeof(char));
			break;

		case 2:
			list = _MakeList(list, sizeof(int));
			break;

		case 3:
			list = _MakeList(list, sizeof(float));
			break;

		case 4:
			list = _MakeList(list, sizeof(double));
			break;

		case 5:
		case 6:
			list = _MakePointerList(list, sizeof(char*));
			break;

		default:
			printf("Tipo indefinido\n");
			return NULL;
	}
	return list;
}

void** teste(void** list){
	list = realloc(list, sizeof(header)+4*sizeof(char*));

	((header*)list)->size = 0;
	((header*)list)->cap = 4;
	((header*)list)->data_size = 8;
	
	return list + sizeof(header);
}

#endif