/*
Lógica principal de um analisador Léxico para C
COPYRIGHTS (C) 2022 João Marcos	
license: GPL3*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "token_model.h"
#include "table.h"

#define INPUT_FILENAME "teste.c"
#define OUTPUT_FILENAME "Lista_de_Tokens.txt"
#define RESERVED_LIST "reserved_words.txt"
#define CONVERSION_TABLE "conversion_table.txt"

#define OP_SINGULAR(_X) (_X == '?' || _X == '%' 	\
		|| _X == '/' || _X == '!')

#define OP_DUPLO(_X) (_X == '+' || _X == '-' 		\
		|| _X == '*' || _X == '|' || _X == '&'		\
		|| _X == '^' || _X == '<' || _X == '>'		\
		|| _X == '=')

#define OPERADOR(_X) (OP_SINGULAR(_X) 				\
		|| OP_DUPLO(_X))

#define SEPARADOR(_X) (OP_SINGULAR(_X) || _X == ':' 	\
		|| _X == ';' || _X == ',' || _X == '.'		\
		|| _X == '(' || _X == ')' || (_X == '{')	\
		|| _X == '}' || _X == '[' || _X == ']')

#define LITERAL_MARKS(_X) (_X == '\'' || _X =='"')

#define SEPARADOR_VAZIO(_X) (_X == ' ' || _X == '\t'\
		|| _X == '\n' || _X == '\r')

#define NUM(_X) (_X >= '0' && _X <= '9')
 
#define ALFA(_X) ((_X >= 'a' && _X <= 'z')			\
		|| (_X >= 'A' && _X <= 'Z')	|| _X == '|')

#define ALFANUM(_X) (NUM(_X) || ALFA(_X))


void writeToken(char* input, int posicao, int sentinela, int line, int column){
	int i;
	int t = posicao - sentinela;

	char* string = malloc(t+1);

	for(i = 0; i < t; i++){
		string[i] = input[sentinela];
		sentinela++;
	}
	if(SEPARADOR_VAZIO(string[i-1]))
		i--;

	string[i] = '\0';
	
	print_token(string);
	printf("%-8d",line);
	printf("%d\n", column-t);

	sentinela--;
}

void fwriteToken(FILE* saida, char* input, int posicao, int sentinela, int line, int column){
	int i;
	int t = posicao - sentinela;

	char* string = malloc(t+1);

	for(i = 0; i < t; i++){
		string[i] = input[sentinela];
		sentinela++;
	}
	if(SEPARADOR_VAZIO(string[i-1]))
		i--;

	string[i] = '\0';
	
	fprint_token(saida, string);
	fprintf(saida, "%-8d",line);
	fprintf(saida, "%d\n", column-t);

	sentinela--;
}

int getTipo(char c){
	if(ALFA(c))
		return 0;

	if(NUM(c))
		return 1;

	if(c == '.')
		return 2;

	if(SEPARADOR(c) || SEPARADOR_VAZIO(c))
		return 3;

	if(OP_DUPLO(c))
		return 4;

	if(c == '"');
		return 5;

	if(c == '\'')
		return 6;	

	return -1;
}

void run(char* input, char* output){

	FILE* arquivo = getInputFile(input);
	FILE* saida = getOutputFile(output);

	char* text = getText(arquivo);
	
	int i = 0;
	int j = 0;

	int i_state = 0;	//Estado no início da iteração
	int f_state = 0;	//Estado após a leitura do próximo char
	
	int line = 1;
	int column = 1;

	printf("%-15s %-20s%-8s%s\n\n","LEXEMA","TOKEN", "L", "C");

	while(text[i] != '\0'){

		f_state = table[i_state][getTipo(text[i])];
		
		if(f_state == -1){
			printf(RED"Erro: "STD"%c   l:"RED"%-5d"STD"%d", text[i], line, column);
			while(!SEPARADOR(text[i]))
				i++;

			j = i;
			i_state = 0;
			continue;
		}
		
		i++;
		column++;

		if(i_state == 4){
			if(!OP_DUPLO(text[i])){
				i--;
			}
			i_state = 0;
		}

		if(f_state == 0){
			
			/*Se o separador for um caractere que gera um token
			o ponteiro de leitura deve ser decrementado, para
			que o token não seja pulado*/
			if(i_state != 0 && (SEPARADOR(text[i-1]) || OPERADOR(text[i-1]))){
				i--;
				column--;
			}
			
			writeToken(text, i, j, line, column);
			fwriteToken(saida, text, i, j, line, column);

			j = i;

			if(OP_DUPLO(text[i]) && ((text[i+1] == text[i])))
				i++;

			while(SEPARADOR_VAZIO(text[i])){
				if(text[i] == '\n'){
				line++;
				column = 1;
			}
				i++;
				j++;
			}
		}
		if(text[i] == '\n'){
			line++;
			column = 1;
		}

		i_state = f_state;
	}
}

void get_args(int argc, char** argv, char** input, char** output){
	char opt = 0;
	while((opt = getopt(argc, argv, "i:o:")) > 0){
		switch(opt){
			case 'i':
				*input = malloc(strlen(optarg));
				strcpy(*input, optarg);
				break;

			case 'o':
				*output = malloc(strlen(optarg));
				strcpy(*output, optarg);
				break;
		}
	}
}

int main(int argc, char** argv){

	char* input_name = INPUT_FILENAME;
	char* output_name = OUTPUT_FILENAME;

	get_args(argc, argv, &input_name, &output_name);
	
	run(input_name, output_name);
}