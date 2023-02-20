#include <string.h>

int scalar(char** line, char*** cCode, int* cWordCount){
	//if the syntax is correct prints the declaration line in cCode
	if(strcmp(line[2], "\n")==0){
		(*cCode)[*cWordCount] = "float ";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = line[1];
		(*cWordCount)++;
		(*cCode)[*cWordCount] = " = 0;\n";
		(*cWordCount)++;
		return 0;
	}
	//else returns 1 (error)
	return 1;
}
