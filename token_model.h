/*
Modelo de tipos de tokens para analisador léxico para C
COPYRIGHTS (C) 2022 João Marcos	
license: GPL3*/

#ifndef _TOKEN_MODEL
#define _TOKEN_MODEL

#include "list3.h"
#include "colors.h"

typedef struct token_types{
	char* key;
	char* value;	
}token_hash;

const token_hash token_types[] = {
	{"!", "NOT"},
	{"\"", "STRING MARK"},
	{"#","MACRO MARK"},
	{"$","MONEY"},
	{"%","MOD"},
	{"&","BIT AND"},
	{"&&","AND"},
	{"'","CHAR MARK"},
	{"(","L PAR"},
	{")","R PAR"},
	{"*","MULT|POINTER"},
	{"**","EXP"},
	{"+","ADD"},
	{"++","ATOMIC ADD"},
	{",","COMMA"},
	{"-","SUB"},
	{"--", "ATOMIC SUB"},
	{".","FIELD ACESS"},
	{"/","DIV"},

	{":","COLON"},
	{";","SEMICOLON"},
	{"<","LESS THAN"},
	{"<<","SHIFT LEFT"},
	{"<=","LESS EQUAL"},
	{"=","ATTR"},
	{"==","EQUAL"},
	{">","GREATER THAN"},
	{">>","SHIFT RIGHT"},
	{">=","GREATER EQUAL"},
	{"?","SHORT IF"},
	{"@",""},
	
	{"bool","BOOLEAN"},
	{"boolean","BOOLEAN"},
	{"case","CASE"},
	{"char","CHAR"},
	{"do","DO"},
	{"double","DOUBLE"},
	{"float","FLOAT"},
	{"for","FOR"},
	{"int","INT"},
	{"real","DOUBLE"},
	{"string","STRING"},
	{"switch","SWITCH"},
	{"while","WHILE"},

	{"[","LBRACKET"},
	{"\\","BSLASH"},
	{"]","RBRACKET"},
	{"^","BIT XOR"},

	{"{","OPEN BLOCK"},
	{"|","BIT OR"},
	{"||","OR"},
	{"}","CLOSE BLOCK"},
	{"~","UNTIL"}
};

const int hash_size = ((sizeof(token_types))/(sizeof(token_hash)));


void print_token(char* input){
	for(int i = 0; i < hash_size; i++){
		if(strEqual(input, token_types[i].key)){
			printf("%-15s "CYAN"%-20s"STD, token_types[i].key, token_types[i].value);
			return;
		}
	}
	if(input[0] == '"'){
		printf("%-15s "ORANGE"%-20s"STD, input, "STRING LITERAL");		
		return;
	}

	if(input[0] >= '0' && input[0] <= '9'){
		printf("%-15s"ORANGE" %-20s"STD, input, "NUM LITERAL");
		return;
	}

	printf("%-15s "GREEN"%-20s"STD, input, "ID");
}

void fprint_token(FILE* saida, char* input){
	for(int i = 0; i < hash_size; i++){
		if(strEqual(input, token_types[i].key)){
			fprintf(saida, "%-15s %-20s", token_types[i].key, token_types[i].value);
			return;
		}
	}
	if(input[0] == '"'){
		fprintf(saida, "%-15s %-20s", input, "STRING LITERAL");		
		return;
	}

	if(input[0] >= '0' && input[0] <= '9'){
		fprintf(saida, "%-15s %-20s", input, "NUM LITERAL");
		return;
	}

	fprintf(saida, "%-15s %-20s", input, "ID");
}

#endif