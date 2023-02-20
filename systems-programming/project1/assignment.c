#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXTOKENS   100 
#define TOKENLENGTH 20  

char tokens[MAXTOKENS][TOKENLENGTH] ;

//extern char lastStr[];
int isNumber(char* number);
int nameAvailable(char* name);
extern char scalars[1024][128];
extern char vectors[1024][128];
extern int vectorDimensions[1024];
extern char matrixArray[1024][128];
extern int matrixDimensions[2048];
char** exprSolver();

int contains(char* str,char ch);
int* matrix_dim_returner(char* str1);
int vector_dim_returner(char* str1);

int assignment(char** line, char*** cCode, int* cWordCount){
	memset(tokens, '\0', sizeof(tokens));



	int index = 0;
	while(line[index] != NULL){
		if(strcmp(line[index], "+")!=0 && strcmp(line[index], "-")!=0 && strcmp(line[index], "*")!=0 && strcmp(line[index], "[")!=0 && strcmp(line[index], "]")!=0 && strcmp(line[index], "{")!=0 && strcmp(line[index], "}")!=0 && strcmp(line[index], "(")!=0 && strcmp(line[index], ")")!=0 && strcmp(line[index], ",")!=0 && strcmp(line[index], "=")!=0){
			if(strcmp(line[index], "tr")!=0 && strcmp(line[index], "sqrt")!=0 && strcmp(line[index], "choose")!=0 && strcmp(line[index], "\n")!=0){
				if(!isNumber(line[index])){
					if(nameAvailable(line[index])){
						printf("%s\n", line[index]);

						printf("burda mı \n");
						return 1;
					}
				}
			}
		}
		index++;
	}
	int type;
	int dimension;
	int dim1;
	int dim2;
	index = 0;
	while(vectors[index][0] != '\0'){
		if(strcmp(vectors[index], line[0])==0){
			type = 1;
			dimension = vectorDimensions[index];
		}
		index++;
	}
	index = 0;
	while(matrixArray[index][0] != '\0'){
		if(strcmp(matrixArray[index], line[0])==0){
			type = 2;
			dim1 = matrixDimensions[2*index];
			dim2 = matrixDimensions[2*index+1];
		}
		index++;
	}
	index = 0;
	while(scalars[index][0] != '\0'){
		if(strcmp(scalars[index], line[0])==0){
			type = 0;
		}
		index++;
	}

	if(strcmp(line[2], "{")==0 && strcmp(line[1], "=")==0){
		if(type ==1){
			if(!(strcmp(line[dimension+3],"}")==0 && strcmp(line[dimension+4],"\n")==0)){
				return 1;
			}
			for(int i=3; i<dimension+3; i++){
				if(!isNumber(line[i])){
					return 1;
				}
				(*cCode)[*cWordCount] = line[0];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = ".values[";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
				sprintf((*cCode)[*cWordCount], "%d", i-2);
				(*cWordCount)++;
				(*cCode)[*cWordCount] = "][1] = ";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = line[i];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = ";\n";
				(*cWordCount)++;
			}
			return 0;
		}
		
		if(type == 2){
			if(!(strcmp(line[dim1*dim2+3],"}")==0 && strcmp(line[dim1*dim2+4],"\n")==0)){
				return 1;
			}
			for(int i=0; i<dim1; i++){
				for(int j=3; j<dim2+3; j++){
					if(!isNumber(line[i*dim2+j])){
						return 1;
					}
					(*cCode)[*cWordCount] = line[0];
					(*cWordCount)++;
					(*cCode)[*cWordCount] = ".values[";
					(*cWordCount)++;
					(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
					sprintf((*cCode)[*cWordCount], "%d", i+1);
					(*cWordCount)++;
					(*cCode)[*cWordCount] = "][";
					(*cWordCount)++;
					(*cCode)[*cWordCount] = malloc(sizeof(char) * 10);
					sprintf((*cCode)[*cWordCount], "%d", j-2);
					(*cWordCount)++;
					(*cCode)[*cWordCount] = "] = ";
					(*cWordCount)++;
					(*cCode)[*cWordCount] = line[i*dim2+j];
					(*cWordCount)++;
					(*cCode)[*cWordCount] = ";\n";
					(*cWordCount)++;
				}
			}
			return 0;
			
		}
	}
	if(type == 0){
		
	}
	index = 0;
	while(strcmp(line[index], "=")!=0){
		index++;
	}
	int eqIndex = index+1;
	index = 0;
	while(line[index][0]!='\n'){
		index++;
	}
	int nlIndex = index;
	
	//char **expression = (char**)malloc(sizeof(char*)*256);

	for(int i=eqIndex; i<nlIndex; i++){
		//expression[i-eqIndex] = line[i];
		strcpy(tokens[i-eqIndex], line[i]);
	}
	char* exprDim;
	index=0;
	while((tokens[index][0]!='\0')){
		index++;
	}
	
	exprDim = exprSolver()[0];
	if(strcmp(exprDim, "\0")==0){
		return 1;
	}
	char* expression;
	expression = exprSolver()[1];

	/*int type;
	index = 0;
	int dimension;
	int dimensions[2];
	while(vectors[index][0] != '\0'){
		if(strcmp(vectors[index], line[0])==0){
			type = 1;
			dimension = vectorDimensions[index];
			break;
		}
		index++;
	}
	index = 0;
	while(scalars[index][0] != '\0'){
		if(strcmp(scalars[index], line[0])==0){
			type = 0;
			break;
		}
		index++;
	}
	index = 0;
	while(matrixArray[index][0] != '\0'){
		if(strcmp(matrixArray[index], line[0])==0){
			type = 2;
			dimensions[0] = matrixDimensions[2*index];
			dimensions[1] = matrixDimensions[2*index+1];
			break;
		}
		index++;
	}*/


	if(strcmp(line[1], "[")==0){
		if(type == 0){
			return 1;
		}
		if(strcmp(line[3], ",")==0){
			if(type == 1){
	printf("geldi mi \n");
				return 1;
			}
			if(isNumber(line[2]) && isNumber(line[4]) && strcmp(line[5], "]")==0){
				if(!isNumber(exprDim)){
					return 1;
				}
				(*cCode)[*cWordCount] = line[0];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = "[";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = line[2];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = "][";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = line[4];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = "] = ";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
				strcpy((*cCode)[*cWordCount], expression);
				//(*cCode)[*cWordCount] = expression;
				(*cWordCount)++;
				(*cCode)[*cWordCount] = ";\n";
				(*cWordCount)++;
				
				return 0;
			}
			return 1;
		}
		if(isNumber(line[2]) && strcmp(line[3], "]")==0){
			if(type == 2){
				return 1;
			}
			if(!isNumber(exprDim)){
				return 1;
			}
			(*cCode)[*cWordCount] = line[0];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "[";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = line[2];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "] = ";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			strcpy((*cCode)[*cWordCount], expression);
			//(*cCode)[*cWordCount] = expression;
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ";\n";
			(*cWordCount)++;
			return 0;
		}
		return 1;
	}

	if(strcmp(line[1], "=")==0){
		if(type == 0){
			if(!isNumber(exprDim)){
				return 1;
			}
			(*cCode)[*cWordCount] = line[0];
			(*cWordCount)++;
			(*cCode)[*cWordCount] = "=";
			(*cWordCount)++;
			(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
			strcpy((*cCode)[*cWordCount], expression);
			(*cWordCount)++;
			(*cCode)[*cWordCount] = ";\n";
			(*cWordCount)++;
			return 0;
		}
		if(type == 1){
			index = 0;
			while(line[index][0] != '\n') {

				printf("%s\n", line[index]);
				index++;
			}
			printf("%s\n", exprDim);
			if(contains(exprDim, '[')){
				if(contains(exprDim, ',')){
					if(dimension != matrix_dim_returner(exprDim)[0]){
						printf("%d %d\n", dimension, matrix_dim_returner(exprDim)[0]);
	printf("geldi mi \n");
						return 1;
					}
				}
				if(dimension != vector_dim_returner(exprDim)){
					return 1;
				}
				(*cCode)[*cWordCount] = "assign(&";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = line[0];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = ", ";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
				strcpy((*cCode)[*cWordCount], expression);
				//(*cCode)[*cWordCount] = expression;
				(*cWordCount)++;
				(*cCode)[*cWordCount] = " );\n";
				(*cWordCount)++;
				return 0;
				
			}
			return 1;

		}
		if(type == 2){
			if(contains(exprDim, '[') && contains(exprDim, ',')){
				if(dim1 != matrix_dim_returner(exprDim)[0] || dim2 != matrix_dim_returner(exprDim)[1]){
					return 1;
				}
				(*cCode)[*cWordCount] = "assign(&";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = line[0];
				(*cWordCount)++;
				(*cCode)[*cWordCount] = ", ";
				(*cWordCount)++;
				(*cCode)[*cWordCount] = (char*)malloc(64*sizeof(char));
				strcpy((*cCode)[*cWordCount], expression);
				//(*cCode)[*cWordCount] = expression;
				(*cWordCount)++;
				(*cCode)[*cWordCount] = " );\n";
				(*cWordCount)++;
				return 0;
				
			}
			return 1;

		}
		return 1;
	}
	
	

	return 1;
}

