#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void split(char**** lexemes);
int scalar(char** line, char*** cCode, int* cWordCount);
int vector(char** line, char*** cCode, int* cWordCount);
int matrix(char** line, char*** cCode, int* cWordCount);
int print(char** line, char*** cCode, int* cWordCount);
int printsep(char** line, char*** cCode, int* cWordCount);
int f4(char** line, char*** cCode, int* cWordCount);
int assignment(char** line, char*** cCode, int* cWordCount);

//holds the names of scalar variables
char scalars[1024][128]; 
//holds the names of vector variables
char vectors[1024][128];
//holds the dimensions of vector variables in the corresponding index
int vectorDimensions[1024];
//holds the names of matrix variables
char matrixArray[1024][128];
//holds the dimensions of vector variables in the corresponding index (index are the 2 times of the index in matrixArray and the following index)
int matrixDimensions[2048];
//holds the name of input file that is given as a argument to main
char *inputName;
//holds the name of the output file that will be written into
char *outputName;

//returns if a string is a number or not (1 if number)
int isNumber(char* number){
	//int index = 0;
	//for every character in a string if it is not a digit returns 0 (string is not a number)
	int dotCount = 0;
	for(int i=0; i<strlen(number); i++){
		if(number[i] == '.'){
			if(dotCount == 0){
				continue;
				dotCount++;
			}
			return 0;
		}
		if(!isdigit(number[i]) && number[i] != ' '){
			return 0;
		}
	}
	/*while(number[index] != '\0'){
		if(!isdigit(number[index])){
			return 0;
		}
		index++;
	}*/
	return 1;
}
//returns if a string is a valid variable name (1 if valid)
int isAlphaNum(char* name){
	//if it is starting with digit it is not valid
	if(isdigit(name[0])){
		return 0;
	}
	int index = 0;
	while(name[index] != '\0'){
		//if there is a character which is not a digit, not a letter and not an underscore, it is not valid
		if(!(isalpha(name[index]) || isdigit(name[index]) || name[index] == '_')){
			return 0;
		}
		index++;
	}
	return 1;
}
//returns if a variable name is taken previously (1 if not taken)
int nameAvailable(char* name){
	int count = 0;
	while(scalars[count][0] != '\0'){
		//searches the name in scalar variables
		if(strcmp(scalars[count], name)== 0){
			return 0;
		}
	count++;
	}
	count = 0;
	while(vectors[count][0] != '\0'){
		//searches the name in vector variables
		if(strcmp(vectors[count], name)== 0){
			return 0;
		}
		count++;
	}
	count = 0;
	while(matrixArray[count][0] != '\0'){
		//searches the name in matrix variables
		if(strcmp(matrixArray[count], name)== 0){
			return 0;
		}
		count++;
	}
	return 1;

}
//opens the output and prints the code that will print the error line in it (takes the line number which has error as an argument)
void printError(int line){
	FILE *output = fopen(outputName, "w");
	fputs("#include <stdio.h>\nint main(){\nprintf(\"Error (Line ", output);
	char *errorLine = malloc(sizeof(char) * 10);
	//converts the line number (which is taken as an int argument) to string
	sprintf(errorLine, "%d", line+1);
	fputs(errorLine, output);
	fputs(")\\n\");\n}", output);
	fclose(output);
}

int main(int argc, char *argv[]){
	//takes the input name as an argument
	inputName = argv[1];
	//output name is the same as input name but .mat is replaced by .c
	outputName = calloc(256,sizeof(char));
	int dotIndex;
	int index = 0;
	while(inputName[index] != '\0'){
		if(inputName[index] == '.'){
			dotIndex = index;
		}
		index++;

	}
	strcpy(outputName, inputName);
	outputName[dotIndex+1] = 'c';
	outputName[dotIndex+2] = '\0';
	outputName[dotIndex+3] = '\0';

	int error = 0;
	//lexemes is a triple dimensional array which the first dimension corresponds to the lines, the second dimension responds to words and the third dimension corresponds to the characters
	char ***lexemes = malloc(sizeof(char*) * 1024);
	int lineCount = 0;
	int wordCount = 0;
	//this function reads the input parse it into lexemes and put it into lexemes array
	split(&lexemes);

	int scalarCount = 0;

	int vectorCount = 0;

	int matrixCount = 0;
	//cCode is the output code that will be written unless there is an error
	char **cCode = malloc(sizeof(char*) * 65536);
	//includes the headers and writes the choose function in the cCode
	cCode[0] = "#include <stdio.h>\n#include <stdlib.h>\n#include <math.h>\nfloat choose(float a, float b, float c, float d){\nif(a==0){\nreturn b;\n}\nif(a>0){\nreturn c;\n}\nif(a<0){\nreturn d;\n}\n}";
	//writes the matrix struct in the cCode
	cCode[1] = "struct Matrix{\nint dims[2];\nfloat values[100][100];\n};\n";
	//writes the matrix constructor in the cCode
	cCode[2] = "struct Matrix newMatrix(int dim1, int dim2){\nstruct Matrix tmp;\ntmp.dims[0] = dim1;\ntmp.dims[1] = dim2;\nfor(int i=1; i<dim1+1; i++){for(int j=1; j<dim2+1; j++){tmp.values[i][j] = 0;}}\nreturn tmp;\n}\n";
	//writes the assign function ( assigns a matrix struct to a matrix struct) in the cCode
	cCode[3] = "void assign(struct Matrix* a, struct Matrix tmp){\nfor(int i=1; i<a->dims[0]+1; i++){\nfor(int j=1; j<a->dims[1]+1; j++){\na->values[i][j] = tmp.values[i][j];\n}\n}\n}";
	//writes the tr function for scalars in the cCode
	cCode[4] = "\nint tr(int a){\nreturn a;\n}\n";
	//writes the tr function for vectors and matrix
	cCode[5] = "\nstruct Matrix trm(struct Matrix a){\nstruct Matrix tmp = newMatrix(a.dims[1], a.dims[0]);\nfor(int i=1; i<a.dims[1]+1; i++){\n";
	cCode[6] = "for(int j=1; j<a.dims[0]+1; j++){\ntmp.values[i][j] = a.values[j][i];\n}\n}\nreturn tmp;\n}\n";
	//writes the sqrt function for the matrix
	cCode[7] = "struct Matrix sqrtm(struct Matrix a){\nstruct Matrix tmp = newMatrix(a.dims[0], a.dims[1]);\nfor(int i=1; i<a.dims[0]+1;i++){";
	cCode[8] = "\nfor(int j=1; j<a.dims[1]+1; j++){\ntmp.values[i][j] = sqrt(a.values[i][j]);\n}\n}\nreturn tmp;\n}\n";
	//writes a function that sums matrix in the cCode
	cCode[9] = "struct Matrix summ(struct Matrix a, struct Matrix b){\nstruct Matrix sum = newMatrix(a.dims[0], a.dims[1]);\nfor(int i=1; i<a.dims[0]+1; i++){\n";
	cCode[10] = "for(int j=1; j<a.dims[1]+1;j++){\nsum.values[i][j] = a.values[i][j]+b.values[i][j];\n}\n}\nreturn sum;\n}\n";
	//writes a function that substracts matrix in the cCode
	cCode[11] = "struct Matrix subm(struct Matrix a, struct Matrix b){\nstruct Matrix diff  = newMatrix(a.dims[0], a.dims[1]);\nfor(int i=1; i<a.dims[0]+1; i++){\n";
	cCode[12] = "for(int j=1; j<a.dims[1]+1;j++){\ndiff.values[i][j] = a.values[i][j]-b.values[i][j];\n}\n}\nreturn diff;\n}\n";
	//writes a function that multiplies matrix in the cCode
	cCode[13] = "struct Matrix productm(struct Matrix a, struct Matrix b){\nstruct Matrix product = newMatrix(a.dims[0], b.dims[1]);\nfor(int i=1; i<a.dims[0]+1; i++){\n";
	cCode[14] = "for(int j=1; j<b.dims[1]+1; j++){\nfor(int k=1; k<a.dims[1]+1; k++){\nproduct.values[i][j] += a.values[i][k]*b.values[k][j];\n}\n}\n}\nreturn product;\n}\n";
	//writes a function that multiplies matrix with a scalar in the cCode
	cCode[15] = "struct Matrix multim(float sca, struct Matrix a){\nstruct Matrix product = newMatrix(a.dims[0],a.dims[1]);\nfor(int i=1; i<a.dims[0]+1;i++){\n";
	cCode[16] = "for(int j=1; j<a.dims[1]+1; j++){\nproduct.values[i][j] = sca * a.values[i][j];\n}\n}\nreturn product;\n}";
	cCode[17] = "float sum(float a, float b){\nreturn a + b;\n}\n";
	cCode[18] = "float sub(float a, float b){\nreturn a - b;\n}\n";
	cCode[19] = "float product(float a, float b){\nreturn a * b;\n}\n";
	//starts the main function 
	cCode[20] = "\nint main(){\n";
	int cWordCount = 21;

	//number of paranthesis that are not yet closed
	int openParanthesis = 0;

	while(lexemes[lineCount] != NULL && error == 0){
		char **line = lexemes[lineCount];
		if(strcmp(line[0], "scalar")==0){
			//if the variable name is not valid throws an error
			if(!isAlphaNum(line[1])){
				error = 1;
			}
			//if the variable name is already taken throws an error
			if(!nameAvailable(line[1])){
				error = 1;
			}
			if(!error){
				//if there is no problem with variable name calls the scalar function which will print the declaration in cCode and will return 1 if there is an error in the line
				error = scalar(line, &cCode, &cWordCount);
				int index = 0;
				while(line[1][index] != '\0'){
					//adds the name of the variable to the scalars array
					scalars[scalarCount][index]=line[1][index];
					index++;
				}
				scalarCount++;
			}
		}
		else if(strcmp(line[0], "vector")==0){
			//if the variable name is not valid throws an error
			if(!isAlphaNum(line[1])){
				error = 1;
			}
			//if the variable name is already taken throws an error
			if(!nameAvailable(line[1])){
				error = 1;
			}
			if(!error){
				//if there is no problem with variable name calls the vector function which will print the declaration in cCode and will return 1 if there is an error in the line
				error = vector(line, &cCode, &cWordCount);
				int index = 0;
				while(line[1][index] != '\0'){
					//adds the name of the variable to the vectors array
					vectors[vectorCount][index]=line[1][index];
					index++;
				}
				//adds the dimension of the variable to the vectorDimensions array
				sscanf(line[3],"%d", &vectorDimensions[vectorCount]);
				vectorCount++;
			}
		}
		else if(strcmp(line[0], "matrix")==0){
			//if the variable name is not valid throws an error
			if(!isAlphaNum(line[1])){
				error = 1;
			}
			//if the variable name is already taken throws an error
			if(!nameAvailable(line[1])){
				error = 1;
			}
			if(!error){
				//if there is no problem with variable name calls the matrix function which will print the declaration in cCode and will return 1 if there is an error in the line
				error =	matrix(line, &cCode, &cWordCount);
				int index = 0;
				while(line[1][index] != '\0'){
					//adds the name of the variable to the vectorArray array
					matrixArray[matrixCount][index]=line[1][index];
					index++;
				}
				//adds the dimensions of the variable to the matrixDimensions array
				sscanf(line[3],"%d", &matrixDimensions[matrixCount*2]);
				sscanf(line[5],"%d", &matrixDimensions[matrixCount*2+1]);
				matrixCount++;
			}
		}
		else if(line[0][0] == '\0'){
			//if the line is completely empty (empty lines or the lines that has comment character at the start of the line) does nothing

		}
		else{
			//if the line is not a declaration line skips to the executable statements block
			break;
		}
		if(error){
			//if an error was detected in the line prints the error printing code in the output
			printError(lineCount);
		}
		lineCount++;
	}
	while(lexemes[lineCount] != NULL && error ==0){
		char **line = lexemes[lineCount];
		//if there is a declaration line in the executable statements block throws an error 
		if(strcmp(line[0], "scalar")==0 || strcmp(line[0], "vector")==0 || strcmp(line[0], "matrix")==0){
			error = 1;
		}
		else if(strcmp(line[0], "printsep")==0){
			//prints the code that will print the seperator in the cCode
			error = printsep(line, &cCode, &cWordCount);
		}
		else if(strcmp(line[0], "print")==0){
			//calls the print function which will print the print function in cCode and will return 1 if there is an error in the line
			error = print(line, &cCode, &cWordCount);
		}
		else if(strcmp(line[0], "for")==0){
			//calls the f4 function which will print the for loop in cCode and will return 1 if there is an error in the line
			error = f4(line, &cCode, &cWordCount);
			if(openParanthesis != 0){
				//if the loop is called while there is an for loop that is not yet closed throws an error
				error = 1;
			}
			//increase the count of paranthesis that has not yet closed
			openParanthesis++;
			if(strcmp(line[3], ",")==0){
				//increase the count of paranthesis that has not yet closed twice if the loop is nested
				openParanthesis++;
			}
		}
		else if(strcmp(line[0], "}")==0){

			if(openParanthesis==1){
				cCode[cWordCount] = "}\n";
				cWordCount++;
				openParanthesis--;
			}
			else if(openParanthesis==2){
				cCode[cWordCount] = "}\n}\n";
				cWordCount++;
				openParanthesis -= 2;
			}
		}
		else{
			//if the line is not an assignment line throws an error (all the other type of lines already covered in the other if statements)
			if(nameAvailable(line[0])){
				error = 1;
			}
			//calls the assignment function which will print the assignment statement in cCode and will return 1 if there is an error in the line
			error = assignment(line, &cCode, &cWordCount);
		}
		if(error){
			//if an error was detected in the line prints the error printing code in the output
			printError(lineCount);
		}
		lineCount++;		
	}
	//if there is an for loop that is not yet closed at the end of the file throws an error
	if(openParanthesis != 0){
		printError(lineCount-1);
	}
	//closes the main function in cCode
	cCode[cWordCount] = "}\n";
	//if there is no error in the input file prints the cCode to the output
	if(!error){
		FILE *output = fopen(outputName, "w");
		cWordCount = 0;
		while(cCode[cWordCount] != NULL && error == 0){
			fputs(cCode[cWordCount], output);
			cWordCount++;
		}
		fclose(output);
	}
	lineCount = 0;
	//free the lexemes array
	while(lexemes[lineCount] != NULL){
		wordCount = 0;
		while(lexemes[lineCount][wordCount] != NULL){
			free(lexemes[lineCount][wordCount]);
			wordCount++;
		}
		free(lexemes[lineCount]);
		lineCount++;
	}

}
