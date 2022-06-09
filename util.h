/*	
util.h
Version: 3	

Autor: Joâo Marcos Sampaio André

*/

#ifndef UTIL__H
#define UTIL__H


#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "colors.h"

#define strLen stringLen
#define len stringLen

//protótipos
void line();
void clear();
int getch();
int ipow(int a, int b);
int strContains(char* string, char* substring);
int strToInt(char* string);
double strToDouble(char* string);
int stringLen(char* string);
void stripSpace(char* string);
char* strPut(char* origem);
char* strConcat(char* str1, char* str2);
void replace(char* string, char ch1, char ch2);
int getLineCount(FILE* arquivo);
_Bool strEqual(char* str1, char* str2);
_Bool strIn(char* str, char** stringList, int length);

char* getText(FILE* arquivo);
int getFileSize(FILE* arquivo);

#define strToArray(_Array, _String) _strToArray(_Array, sizeof(_Array)/(sizeof(*(_Array))), _String);
//===============================

void line(){
	printf("===================================\n");
}

void clear(){
	system("clear");
}

int getch(){
	struct termios oldattr, newattr;
    
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

int ipow(int a, int b){
	int r = a;
	
	if(b <= 0) return 1;

	while(b-- > 1){
		r = r*a;
	}
	return r;
}

double fpow(double a, int b){
	double r;

	if(b > 0){
		r = a;
	}
	else r = 1/a;

	if(b == 0)return 1;

	while(++b < 1){
		r = r/a;
	}

	while(--b > 1){
		r = r*a;
	}

	return r;
}


int strContains(char* string, char* substring){
	int i = 0;
	int j = 0;

	while(string[i] != '\0'){
		if(substring[j] == '\0')return 1;

		if(string[i] != substring[j]){
			j = 0;
			i++;
			continue;	
		};
		
		i++;
		j++;
		
	}
	if(substring[j] == '\0')return 1;

	return 0;
}

int stoi(char* string){
    int value = 0;
    int exp = 1;
    
    int t = (stringLen(string));

    for(int i = t-1; i >= 0; i--){
        value = value + ((string[i]-48)*exp);
        exp = exp*10;
    }
    
    return value;
}

double strToDouble(char* string){
	int t = stringLen(string);
	int i;
	int zero = t;

	double parte_inteira = 0;
	double parte_decimal = 0;

	for(i = 0; i < t; i++){
		if(string[i] == '.');
		zero = i;
	}
	//012345
	//152.52
	for(i = zero-1; i >= 0; i--){
		parte_inteira = parte_inteira + ((string[i]-48)*ipow(10, zero-1-i));
	}

	for(i = zero+1; i < t; i++){
		parte_decimal = parte_decimal;
	}
}

int stringLen(char* string){
	int len = 0;
	while(string[len++] != '\0');

	return len-1;
}

void stripSpace(char* string){
	int t = stringLen(string)-1;
	while(string[t] == ' ')t--;
	string[t+1] = '\0';
}

char* _strToArray(char *array, int size, char* string){
	int strSize = stringLen(string);
	int i;
	if(strSize > size){
		printf(RED"Failed in StrToArray(Array, String) call. String greater than array size.\n"STD);
		printf("Array Size: %-8d String: "ORANGE"%s\n"STD, size, string);
		return NULL;
	}

	for(i = 0; i < strSize; i++){
		array[i] = string[i];
	}

	if(i <= size){
		array[i] = '\0';
	}

	return array;
}

char* strPut(char* src){
	int t = stringLen(src);
	char* dest = malloc(t+1);
	int i = 0;
	
	for(i; i<t; i++){
		dest[i] = src[i];
	}

	dest[i] = '\0';

	return dest;
}

void strPut2(char** dest, char* src){

	int t = stringLen(src);
	if(*dest = realloc(*dest, t+1))
		printf("alocado");
	int i;

	for(i = 0; i < t; i++){
		*dest[i] = src[i];
	}

	*dest[i] = '\0';
	printf("ss: %s\n", src);
}

char* strConcat(char* str1, char* str2){
	int size = stringLen(str1)+stringLen(str2)+1;
	char* string = malloc(size);
	int i = 0;
	
	while(*str1  != '\0'){
		string[i] = *str1++;
		i++;
	}

	while(*str2 != '\0'){
		string[i] = *str2++;
		i++;
	}
	string[i] = '\0';

	return string;
}

void replace(char* string, char ch1, char ch2){
	int t = stringLen(string);
	for(int i = 0; i < t; i++){
		if(string[i] == ch1){
			string[i] = ch2;
		}
	}
}

int getLineCount(FILE* arquivo){
	char c;
	int count = 1;

	while(fscanf(arquivo, "%c", &c) > 0){
		if(c == '\n')
			count++;
	}

	/* Desconsiderar \n extra no fim do arquivo se houver
	
	*/
	fscanf(arquivo, "%c", &c);
	if(c == '\n'){
		count--;
	}

	//Voltar pointeiro do arquivo para inicio
	fseek(arquivo, 0, SEEK_SET);
	
	return count;
}

_Bool strEqual(char *str1, char* str2){
	int i = 0;
	while(str1[i] == str2[i]){
		if(str1[i++

] == '\0')
			return 1;
	}
	return 0;
}

_Bool strIn(char* str, char** strlist, int length){

	int i;
	for(i = 0; i < length; i++){
		if(strEqual(str, strlist[i]))
			return 1;
	}
	return 0;
}

char* getText(FILE* arquivo){
	char* text;

	int t = getFileSize(arquivo);

	if(arquivo == NULL){
		printf(RED"Arquivo não aberto"STD);
		return NULL;
	}

	text = malloc(t);


	while(fscanf(arquivo, "%c", text++) > 0);

	return text-t-1;
}

int getFileSize(FILE* arquivo){
	int t;
	fseek(arquivo, 0, SEEK_END);
	t = ftell(arquivo);
	fseek(arquivo, 0, SEEK_SET);

	return t;
}

FILE* getInputFile(char* filename){
	FILE* arquivo = fopen(filename, "r");
	if(arquivo == NULL){
		printf(RED"Falha ao abrir o arquivo: "STD"%s\n", filename);\
	}
	return arquivo;
}

FILE* getOutputFile(char* filename){
	FILE* arquivo = fopen(filename, "w+");
	if(arquivo == NULL){
		printf(RED"Falha ao abrir o arquivo: "STD"%s\n", filename);
	}

	return arquivo;
}
#endif