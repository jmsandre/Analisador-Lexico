/*Definições de macros para cores no terminal
e testes

for this specific file:
	COPYRIGHT FREE
	NO WARRANTY
*/

#ifndef _COLORS_H
#define _COLORS_H

#include <stdarg.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define PURPLE "\033[1;35m"
#define BLUE "\033[0;34m"
#define ORANGE "\033[1;33m"
#define STD "\033[m"

#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGS(...) ELEVENTH_ARGUMENT(dummy, ## __VA_ARGS	__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


//int print(const char* string, ...){
	//Máximo de 10 argumentos
//	int x = COUNT_ARGS("Teste","ArgNUm", "f");
//	printf("Arg count: %d\n", x);
//}	

int printRed(const char* string, ...){

}

int printGreen(){

}

int printCyan(){

}

int printPurple(){

}

int printBlue(){

}

int printOrange(){

}

#endif