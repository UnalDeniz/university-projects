#include <string.h>
#include <ctype.h>
#include <stdio.h>

int isNumber(char* number);

int matrix(char** line, char*** cCode, int* cWordCount){
	//if the indexes in the matrix declaration are not numbers throws an error
	if(!(isNumber(line[3]) && isNumber(line[5]))){
		return 1;
	}
	//checks if the syntax is correct, if it is writes the declaration line in cCode
	if(strcmp(line[2], "[")==0 && strcmp(line[4], ",")==0 && strcmp(line[6], "]")==0 && strcmp(line[7], "\n")==0){
		(*cCode)[*cWordCount] = "struct Matrix ";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = line[1];
		(*cWordCount)++;
		(*cCode)[*cWordCount] = "  = newMatrix(";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = line[3];
		(*cWordCount)++;
		(*cCode)[*cWordCount] = ", ";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = line[5];
		(*cWordCount)++;
		(*cCode)[*cWordCount] = ");\n";
		(*cWordCount)++;
		return 0;
	}
	//if the syntax is not correct returns 1
	return 1;
}
