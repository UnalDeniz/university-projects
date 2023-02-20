#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXTOKENS   100 
#define TOKENLENGTH 20  

char tokens[MAXTOKENS][TOKENLENGTH] ;

extern char scalars[1024][128];
extern char vectors[1024][128];
extern int vectorDimensions[1024];
extern char matrixArray[1024][128];
extern int matrixDimensions[2048];

char** exprSolver();
int isNumber(char* number);

int print(char** line, char*** cCode, int* cWordCount){
	if(strcmp(line[1], "(")!=0){
		return 1;
	}
	char type[6] = {'\0','\0','\0','\0','\0','\0'};
	int index = 0;
	int dimension;
	int dimensions[2];
	while(vectors[index][0] != '\0'){
		if(strcmp(vectors[index], line[2])==0){
			//type = "vector";
			type[0] = 'v'; type[1] = 'e'; type[2] = 'c'; type[3] = 't'; type[4] = 'o'; type[5] = 'r'; 
			dimension = vectorDimensions[index];
			break;
		}
		index++;
	}
	index = 0;
	while(scalars[index][0] != '\0'){
		if(strcmp(scalars[index], line[2])==0){
			//type = "scalar";
			type[0] = 's'; type[1] = 'c'; type[2] = 'a'; type[3] = 'l'; type[4] = 'a'; type[5] = 'r'; 
		}
		index++;
	}
	index = 0;
	while(matrixArray[index][0] != '\0'){
		if(strcmp(matrixArray[index], line[2])==0){
			//type = "matrix";
			type[0] = 'm'; type[1] = 'a'; type[2] = 't'; type[3] = 'r'; type[4] = 'i'; type[5] = 'x'; 
			dimensions[0] = matrixDimensions[2*index];
			dimensions[1] = matrixDimensions[2*index+1];
		}
		index++;
	}
	if(type[0]=='\0'){
		return 1;
	}
	index = 0;
	int paranIndex;
	int paranCount = 0;
	while(strcmp(line[index], "\n")!=0){
		if(strcmp(line[index], ")")==0){
			paranIndex = index;
			paranCount++;
		}
		index++;

	}
	if(paranCount == 0){
		return 1;
	}
	if(strcmp(line[paranIndex+1], "\n")!=0){
		return 1;
	}
	if(paranIndex == 3){	
		if(strcmp(type, "scalar")==0){
			(*cCode)[*cWordCount] = "if(";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " - (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " < 0.000001){\nprintf(\"%d\\n\", (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ");\n} else {\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "printf(\"%f\\n\", ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ");\n}\n";
			(*cWordCount)++;
			/*int wordCount = 0;
			while(line[wordCount] != NULL){
				if(strcmp(line[wordCount], "print")==0){
					(*cCode)[*cWordCount] = "printf";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "(")==0){
					(*cCode)[*cWordCount] = "(\"%f\\n\",";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "\n")==0){
					(*cCode)[*cWordCount] = ";";
					(*cWordCount)++;
				}
				(*cCode)[*cWordCount] = line[wordCount];
				(*cWordCount)++;
				wordCount++;
			}*/
			return 0;
		}
		if(strcmp(type, "vector")==0){
			(*cCode)[*cWordCount] = "for(int z=1; z<";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
			sprintf((*cCode)[*cWordCount], "%d", dimension+1);
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; z++){\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "if(";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[z][1] - (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[z][1] < 0.000001){\nprintf(\"%d\\n\", (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[z][1]);\n} else {\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "printf(\"%f\\n\", ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[z][1]);\n}\n}\n";
			(*cWordCount)++;
			
			/*int wordCount = 0;
			while(line[wordCount] != NULL){
				if(strcmp(line[wordCount], "print")==0){
					(*cCode)[*cWordCount] = "printf";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(wordCount==2){
					(*cCode)[*cWordCount] = line[wordCount];
					(*cWordCount)++;
					(*cCode)[*cWordCount] = ".values[z][1]";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "(")==0){
					(*cCode)[*cWordCount] = "(\"%f\\n\",";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "\n")==0){
					(*cCode)[*cWordCount] = ";";
					(*cWordCount)++;
				}
				(*cCode)[*cWordCount] = line[wordCount];
				(*cWordCount)++;
				wordCount++;
			}
			(*cCode)[*cWordCount] = "}\n}\n";
			(*cWordCount)++;*/
			return 0;
		}
		if(strcmp(type, "matrix")==0){
			(*cCode)[*cWordCount] = "for(int y=1; y<";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
			sprintf((*cCode)[*cWordCount], "%d", dimensions[0]+1);
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; y++){\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "for(int z=1; z<";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
			sprintf((*cCode)[*cWordCount], "%d", dimensions[1]+1);
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; z++){\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "if(";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[y][z] - (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[y][z] < 0.000001){\nprintf(\"%d\\n\", (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[y][z]);\n} else {\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "printf(\"%f\\n\", ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ".values[y][z]);\n}\n}\n";
			(*cWordCount)++;
			/*int wordCount = 0;
			while(line[wordCount] != NULL){
				if(strcmp(line[wordCount], "print")==0){
					(*cCode)[*cWordCount] = "printf";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(wordCount==2){
					(*cCode)[*cWordCount] = line[wordCount];
					(*cWordCount)++;
					(*cCode)[*cWordCount] = ".values[y][z]";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "(")==0){
					(*cCode)[*cWordCount] = "(\"%f\\n\",";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "\n")==0){
					(*cCode)[*cWordCount] = ";";
					(*cWordCount)++;
				}
				(*cCode)[*cWordCount] = line[wordCount];
				(*cWordCount)++;
				wordCount++;
			}
			(*cCode)[*cWordCount] = "}\n}\n";
			(*cWordCount)++;*/
			return 0;
		}
	}
	//return 0;
	/*if(strcmp(line[3], "[")==0 && strcmp(line[paranIndex-1], "]")!=0){
		memset(tokens, '\0', sizeof(tokens));

		for(int i=4; i<paranIndex-1; i++){
			strcpy(tokens[i-4], line[i]);
		}
		char *exprDim = exprSolver()[0];
		char *expression = exprSolver()[1];
		if(!isNumber(exprDim)){
			return 1;
		}

		if(strcmp(type, "scalar")==0){
			return 1;
		}
		if(strcmp(type, "vector")==0){
				
			(*cCode)[*cWordCount] = "printf(\"%f\\n\",";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "[";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = expression;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "]);\n";
			(*cWordCount)++;

			return 0;

			int wordCount = 0;
			while(line[wordCount] != NULL){
				if(strcmp(line[wordCount], "print")==0){
					(*cCode)[*cWordCount] = "printf";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "(")==0){
					(*cCode)[*cWordCount] = "(\"%f\\n\",";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "\n")==0){
					(*cCode)[*cWordCount] = ";";
					(*cWordCount)++;
				}
				(*cCode)[*cWordCount] = line[wordCount];
				(*cWordCount)++;
				wordCount++;
			}
			return 0;*/

		/*}
		if(strcmp(type, "matrix")==0){
			return 1;
			(*cCode)[*cWordCount] = "for(int z=0; z<";
			(*cWordCount)++;
			//(*cCode)[*cWordCount] = dimensions[1];
			(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
			sprintf((*cCode)[*cWordCount], "%d", dimensions[1]);
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; z++){\n";
			(*cWordCount)++;
			int wordCount = 0;
			while(line[wordCount] != NULL){
				if(strcmp(line[wordCount], "print")==0){
					(*cCode)[*cWordCount] = "printf";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "]")==0){
					(*cCode)[*cWordCount] = "][z]";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "(")==0){
					(*cCode)[*cWordCount] = "(\"%f\\n\",";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "\n")==0){
					(*cCode)[*cWordCount] = ";";
					(*cWordCount)++;
				}
				(*cCode)[*cWordCount] = line[wordCount];
				(*cWordCount)++;
				wordCount++;
			}
			(*cCode)[*cWordCount] = "}\n";
			(*cWordCount)++;
			return 0;*/
		/*}
	}
	if(strcmp(line[3], "[")==0 && strcmp(line[5], ",")==0 && strcmp(line[7], "]")==0 && strcmp(line[8], ")")==0 && strcmp(line[9], "\n")==0){
		if(strcmp(type, "scalar")==0){
			return 1;
		}
		if(strcmp(type, "vector")==0){
			return 1;
		}
		memset(tokens, '\0', sizeof(tokens));

		for(int i=4; i<paranIndex-1; i++){
			strcpy(tokens[i-4], line[i]);
		}
		char *exprDim = exprSolver()[0];
		char *expression = exprSolver()[1];
		if(!isNumber(exprDim)){
			return 1;
		}
		if(strcmp(type, "matrix")==0){
			int wordCount = 0;
			while(line[wordCount] != NULL){
				if(strcmp(line[wordCount], "print")==0){
					(*cCode)[*cWordCount] = "printf";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(wordCount == 2){
					(*cCode)[*cWordCount] = line[2];
					(*cWordCount)++;
					(*cCode)[*cWordCount] = ".values";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "(")==0){
					(*cCode)[*cWordCount] = "(\"%f\\n\",";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], ",")==0){
					(*cCode)[*cWordCount] = "][";
					(*cWordCount)++;
					wordCount++;
					continue;
				}
				if(strcmp(line[wordCount], "\n")==0){
					(*cCode)[*cWordCount] = ";";
					(*cWordCount)++;
				}
				(*cCode)[*cWordCount] = line[wordCount];
				(*cWordCount)++;
				wordCount++;
			}
			return 0;
		}
	}*/
	memset(tokens, '\0', sizeof(tokens));

	printf("girdin mi 1\n");
	for(int i=2; i<paranIndex; i++){
		printf("%s\n", line[i]);
		strcpy(tokens[i-2], line[i]);
	}
	printf("girdin mi  2\n");
	char *exprDim;
	exprDim = exprSolver()[0];
	char *expression;
	expression = exprSolver()[1];
	if(isNumber(exprDim)){
	
		(*cCode)[*cWordCount] = "if(";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = expression;
		(*cWordCount)++;
		(*cCode)[*cWordCount] = " - (int)";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = expression;
		(*cWordCount)++;
		(*cCode)[*cWordCount] = " < 0.000001){\nprintf(\"%d\\n\", (int)";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = expression;
		(*cWordCount)++;
		(*cCode)[*cWordCount] = ");\n} else {\n";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = "printf(\"%f\\n\",";
		(*cWordCount)++;
		(*cCode)[*cWordCount] = expression;
		(*cWordCount)++;
		(*cCode)[*cWordCount] = ");\n}\n";
		//(*cCode)[*cWordCount] = ");\n";
		(*cWordCount)++;

		return 0;
	}

			/*(*cCode)[*cWordCount] = "if(";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " - (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " < 0.000001){\nprintf(\"%d\\n\", (int)";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ");\n} else {\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "printf(\"%f\\n\", ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ");\n}\n}\n";
			(*cWordCount)++;
			*int wordCount = 0;*/

	return 1;
}

