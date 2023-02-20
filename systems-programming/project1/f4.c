#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTOKENS   100 
#define TOKENLENGTH 20  

extern char tokens[MAXTOKENS][TOKENLENGTH] ;

int isNumber(char* number);
char** exprSolver();

int f4(char** line, char*** cCode, int* cWordCount){
	if(strcmp(line[1], "(")!=0){
		return 1;
	}
	int cIndex[4];
	int cParanIndex;
	int commaIndex;
	int pIndex = 0;
	int coIndex = 0;
	int index = 0;
	int colIndex = 0;
	while(strcmp(line[index], "\n")!=0){
		if(strcmp(line[index], ":")==0){
			if(colIndex>3){
				return 1;
			}
			cIndex[colIndex] = index;
			colIndex++;
		}
		if(strcmp(line[index], ")")==0){
			cParanIndex = index;
			pIndex++;
		}
		index++;
	}
	index = 0;
	if(colIndex == 4){
		while(strcmp(line[index], "\n")!=0){
			if(index < cIndex[1] || index > cIndex[2]){
				index++;
				continue;
			}
			if(strcmp(line[index], ",")==0){
				memset(tokens, '\0', sizeof(tokens));
				char *tmp = (char*)calloc(256,sizeof(char));
				for(int i=cIndex[1]+1; i<index; i++){
					strcpy(tokens[i-cIndex[1]-1], line[i]);
				}
	printf("bitti mi \n");
				if(!isNumber(exprSolver()[0])){
					free(tmp);
					index++;
					continue;
				}
				memset(tokens, '\0', sizeof(tokens));
				tmp = (char*)calloc(256,sizeof(char));
				for(int i=index+1; i<cIndex[2]; i++){
					strcpy(tokens[i-index-1], line[i]);
				}
				if(!isNumber(exprSolver()[0])){
					free(tmp);
					index++;
					continue;
				}

				commaIndex = index;
				coIndex++;
			}
			index++;
		}
	}
	if(!((colIndex == 2 && coIndex == 0 && pIndex > 0)||(colIndex == 4 && coIndex >= 1 && pIndex > 0))){
		return 1;
	}
	memset(tokens, '\0', sizeof(tokens));
	char *firstExpr = (char*)calloc(256,sizeof(char));
	for(int i=4; i<cIndex[0]; i++){
		strcpy(tokens[i-4], line[i]);
	}
	if(!isNumber(exprSolver()[0])){
		return 1;
	}
	strcpy(firstExpr, exprSolver()[1]);
	//firstExpr = exprSolver()[1];

	memset(tokens, '\0', sizeof(tokens));
	char *secondExpr = (char*)calloc(256,sizeof(char));
	for(int i=cIndex[0]+1; i<cIndex[1]; i++){
		strcpy(tokens[i-cIndex[0]-1], line[i]);
	}
	if(!isNumber(exprSolver()[0])){
		return 1;
	}
	strcpy(secondExpr, exprSolver()[1]);
	//secondExpr = exprSolver()[1];

	if(colIndex == 2){
		if(cParanIndex < cIndex[1]){
			return 1;
		}
		memset(tokens, '\0', sizeof(tokens));
		char *thirdExpr = (char*)calloc(256,sizeof(char));
		for(int i=cIndex[1]+1; i<cParanIndex; i++){
			strcpy(tokens[i-cIndex[1]-1], line[i]);
		}
		if(!isNumber(exprSolver()[0])){
			return 1;
		}
		strcpy(thirdExpr, exprSolver()[1]);
		//thirdExpr = exprSolver()[1];

		if(strcmp(line[3], "in")==0 && strcmp(line[cParanIndex+1], "{")==0 && strcmp(line[cParanIndex+2], "\n")==0){
			(*cCode)[*cWordCount] = "for(int ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " =";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], firstExpr);
			(*cCode)[*cWordCount] = firstExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " <=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], secondExpr);
			(*cCode)[*cWordCount] = secondExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " +=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], thirdExpr);
			(*cCode)[*cWordCount] = thirdExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "){\n";
			(*cWordCount)++;
			return 0;
		}
	}
	if(colIndex == 4){
		if(cParanIndex < cIndex[3]){
			return 1;
		}
		memset(tokens, '\0', sizeof(tokens));
		char *thirdExpr = (char*)calloc(256,sizeof(char));
		for(int i=cIndex[1]+1; i<commaIndex; i++){
			strcpy(tokens[i-cIndex[1]-1], line[i]);
		}
		if(!isNumber(exprSolver()[0])){
			return 1;
		}
		strcpy(thirdExpr, exprSolver()[1]);
		//thirdExpr = exprSolver()[1];
		memset(tokens, '\0', sizeof(tokens));
		char *fourthExpr = (char*)calloc(256,sizeof(char));
		for(int i=commaIndex+1; i<cIndex[2]; i++){
			strcpy(tokens[i-commaIndex-1], line[i]);
		}
		if(!isNumber(exprSolver()[0])){
			return 1;
		}
		strcpy(fourthExpr, exprSolver()[1]);
		//fourthExpr = exprSolver()[1];
		memset(tokens, '\0', sizeof(tokens));
		char *fifthExpr = (char*)calloc(256,sizeof(char));
		for(int i=cIndex[2]+1; i<cIndex[3]; i++){
			strcpy(tokens[i-cIndex[2]-1], line[i]);
		}
		if(!isNumber(exprSolver()[0])){
			return 1;
		}
		strcpy(fifthExpr, exprSolver()[1]);
		//fifthExpr = exprSolver()[1];
		memset(tokens, '\0', sizeof(tokens));
		char *sixthExpr = (char*)calloc(256,sizeof(char));
		for(int i=cIndex[3]+1; i<cParanIndex; i++){
			strcpy(tokens[i-cIndex[3]-1], line[i]);
		}
		if(!isNumber(exprSolver()[0])){
			return 1;
		}
		strcpy(sixthExpr, exprSolver()[1]);
		//sixthExpr = exprSolver()[1];
		if(strcmp(line[5], "in")==0 && strcmp(line[cParanIndex+1], "{")==0 && strcmp(line[cParanIndex+2], "\n")==0){
			(*cCode)[*cWordCount] = "for(int ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " =";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], firstExpr);
			(*cCode)[*cWordCount] = firstExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " <=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], secondExpr);
			(*cCode)[*cWordCount] = secondExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " +=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], thirdExpr);
			(*cCode)[*cWordCount] = thirdExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "){\n";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "for(int ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[4];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " =";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], fourthExpr);
			(*cCode)[*cWordCount] = fourthExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[4];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " <=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], fifthExpr);
			(*cCode)[*cWordCount] = fifthExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "; ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[4];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = " +=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			//strcpy((*cCode)[*cWordCount], sixthExpr);
			(*cCode)[*cWordCount] = sixthExpr;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "){\n";
			(*cWordCount)++;
			return 0;
		}
	}

		printf("burası mı \n");
	return 1;
}
