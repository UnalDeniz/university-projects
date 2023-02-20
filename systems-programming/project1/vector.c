#include <string.h>
#include <ctype.h>
#include <stdio.h>

int isNumber(char* number);

int vector(char** line, char*** cCode, int* cWordCount){
	//if the array size is not a number returns 1 (error)
	if(!isNumber(line[3])){
		return 1;
	}
	//if the syntax is correct prints the declaration line in the cCode
	if(strcmp(line[2], "[")==0 && strcmp(line[4], "]")==0 && strcmp(line[5], "\n")==0){
		(*cCode)[*cWordCount] = "struct Matrix ";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = line[1];
		(*cWordCount)++;
		(*cCode)[*cWordCount] = "  = newMatrix(";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = line[3];
		(*cWordCount)++;
		(*cCode)[*cWordCount] = ", 1);\n";
		(*cWordCount)++;

		return 0;
	}
	//else returns 1 (error)
	return 1;
}
