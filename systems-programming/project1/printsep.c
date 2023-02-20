#include <string.h>

int printsep(char** line, char*** cCode, int* cWordCount){
	//this file prints the seperator printing file to cCode if the syntax is correct
	if(strcmp(line[1], "(")==0 && strcmp(line[2], ")")==0 && strcmp(line[3], "\n")==0){
		(*cCode)[*cWordCount] = "printf(\"------------\\n\");\n";
		(*cWordCount)++;
		return 0;
	}
	//returns 1 if the syntax is wrong
	return 1;
}
