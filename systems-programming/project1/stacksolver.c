#include "stack.h"

char* stackSolver(char*, int);
char* searcher(char *str);
int is_integer(char *token);
int vector_dim_returner(char* str1);
int* matrix_dim_returner(char* str1);
int contains(char* str,char ch);

/*
int main(){
    
    stackSolver(strdup("[5,3] kl * kl ab + 3 +"));
	
    return 0;
}
*/

char* stackSolver(char *str, int check){
	
    char parts[2048][256];
    
    for(int k=0;k<2048;k++){
    	memset(parts[k], '\0', sizeof(256));
    }
	
    if(str[0]=='\0'){
		return "\0";
	}
    char* token = strtok(str," ");
    // loop through the string to extract all other tokens
    
    int index1=0;

    
    while( token != NULL ) {
       strcpy(parts[index1],token);
       token = strtok(NULL, " ");
       index1++;

    }
    
    
    int indForTr=0;
    
    while(parts[indForTr][0]!='\0'){
		
    	//printf("%s\n",parts[indForTr]);
    	if(strcmp(parts[indForTr],"+")==0 || strcmp(parts[indForTr],"-")==0 || strcmp(parts[indForTr],"*")==0)
    	{
    		// bisi yapma
    	}
    	else if(parts[indForTr][0]=='[' || is_integer(parts[indForTr]))
    	{
    		// bisi yapma
    	}
    	else{
			printf ("PART 1  %s \n", parts[indForTr]);
    		strcpy(parts[indForTr],searcher(parts[indForTr]));
			if(strcmp(parts[indForTr],"-1")==0){
				return "\0";
			}
    		//printf("%s\n", parts[indForTr]);
			printf ("PART  2 %s \n", parts[indForTr]);

    	}
    	
    	//printf("%s\n","TRUE");
    	indForTr++;
    }
    
    //BEFORE STACK OPERATION TRANSLATE EVERYTHING TO DIMS
    

    
    struct Stack* stack = createStack(1000);
    
    if (!stack) return "\0";
    
  

   
    

    
    int i=0;
    //Traversing the stack
    while(parts[i][0]!='\0'){
		if(parts[i+1][0]=='\0' && (parts[i][0]=='*' || parts[i][0]=='-' ||parts[i][0]=='+') && !check && !isEmpty(stack)){
			//printf("Peek %s\n",peek(stack));
//			return(peek(stack));

		}
    	//Not an operation
    	if((parts[i][0]=='[' || is_integer(parts[i]))){
			//printf("Push %s\n",parts[i]);
    		push(stack, parts[i]);

    	}
    	
    	else{

    		//Operation's calculations pop and push...
    	    char *operand2=pop(stack); //[3] [3,3] 3 
    	    char *operand1=pop(stack);
			printf ("OPERAND 1 %s \n", operand1);
			printf ("OPERAND 2 %s \n", operand1);
    	    if(strcmp(parts[i],"+")==0||strcmp(parts[i],"-")==0){
    	    	if(operand1[0]=='[' && operand2[0]=='[' && contains(operand1,',') && contains(operand2,',')){
    	    			int *operand1_dim=matrix_dim_returner(operand1);
    	    			int *operand2_dim=matrix_dim_returner(operand2);
    	    			
    	    			if(operand1_dim[0]==operand2_dim[0] && operand1_dim[1]==operand2_dim[1]){
    	    				
    	    				push(stack, operand1);
    	    				
    	    			}
    	    			else{
    	    				printf("SumMatrix Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		}
    	    		else if(operand1[0]=='[' && operand2[0]=='[' && contains(operand1,',') && !contains(operand2,',')){
    	    			int *operand1_dim=matrix_dim_returner(operand1);
    	    			int operand2_dim=vector_dim_returner(operand2);
    	    			if(operand1_dim[1]==1 && operand1_dim[0]==operand2_dim){
    	    				push(stack, operand1);
    	    			}
    	    			else{
    	    				printf("SumMatrix-Vector Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		
    	    		}
    	    		
    	    		else if(operand1[0]=='[' && operand2[0]=='[' && !contains(operand1,',') && contains(operand2,',')){
    	    			int *operand2_dim=matrix_dim_returner(operand2);
    	    			int operand1_dim=vector_dim_returner(operand1);
    	    			if(operand2_dim[1]==1 && operand2_dim[0]==operand1_dim){
    	    				push(stack, operand2);
    	    			}
    	    			else{
    	    				printf("SumVector-Matrix Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		
    	    		}
    	    		else if(operand1[0]=='[' && operand2[0]=='[' && !contains(operand1,',') && !contains(operand2,',')){
    	    			int operand2_dim=vector_dim_returner(operand2);
    	    			int operand1_dim=vector_dim_returner(operand1);
    	    			if(operand2_dim==operand1_dim){
    	    				push(stack, operand2);
    	    			}
    	    			else{
    	    				printf("SumVector-Vector Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		}
    	    		else if(is_integer(operand1)&&is_integer(operand2)){
    	    			push(stack,operand1);
    	    		}
    	    		else{
    	    			printf("STACK + Operation Error!\n");
    	    			return "\0";
    	    		}	    	
    	    }
    	    else if(strcmp(parts[i],"*")==0){
    	    	if(operand1[0]=='[' && operand2[0]=='[' && contains(operand1,',') && contains(operand2,',')){
						
    	    			int *operand1_dim=matrix_dim_returner(operand1);
    	    			int *operand2_dim=matrix_dim_returner(operand2);
    	    			
    	    			if(operand1_dim[1]==operand2_dim[0]){
    	    				
    	    				char mulDim[100];
    	    				memset(mulDim, '\0', sizeof(mulDim));
    	    				strcpy(mulDim,"[");
    	    				char tmp[100];
    	    				memset(tmp, '\0', sizeof(tmp));
    	    				sprintf(tmp,"%d",operand1_dim[0]);
    	    				strcat(mulDim,tmp);
    	    				strcat(mulDim,",");
    	    				memset(tmp, '\0', sizeof(tmp));
    	    				sprintf(tmp,"%d",operand2_dim[1]);
    	    				strcat(mulDim,tmp);
    	    				strcat(mulDim,"]");
    	    				push(stack, mulDim);
    	    				
    	    				
    	    			}
    	    			else{
    	    				printf("PrdMatrix Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		}
    	    		else if(operand1[0]=='[' && operand2[0]=='[' && contains(operand1,',') && !contains(operand2,',')){

    	    			int *operand1_dim=matrix_dim_returner(operand1);
    	    			int operand2_dim=vector_dim_returner(operand2);
    	    			if(operand1_dim[1]==operand2_dim){
    	    				char mulDim[100];
    	    				memset(mulDim, '\0', sizeof(mulDim));
    	    				strcpy(mulDim,"[");
    	    				char tmp[100];
    	    				memset(tmp, '\0', sizeof(tmp));
    	    				sprintf(tmp,"%d",operand1_dim[0]);
    	    				strcat(mulDim,tmp);
    	    				strcat(mulDim,",1]");
    	    				push(stack, mulDim);
    	    	
    	    			}
    	    			else{
    	    				printf("PrdMatrix-Vector Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		}
    	    		else if(operand1[0]=='[' && operand2[0]=='[' && !contains(operand1,',') && contains(operand2,',')){

    	    			int *operand2_dim=matrix_dim_returner(operand2);
    	    			int operand1_dim=vector_dim_returner(operand1);
    	    			if(operand2_dim[0]==1){
    	    				char mulDim[100];
    	    				memset(mulDim, '\0', sizeof(mulDim));
    	    				strcpy(mulDim,"[");
    	    				char tmp[100];
    	    				memset(tmp, '\0', sizeof(tmp));
    	    				sprintf(tmp,"%d",operand1_dim);
    	    				strcat(mulDim,tmp);
    	    				strcat(mulDim,",");
    	    				memset(tmp, '\0', sizeof(tmp));
    	    				sprintf(tmp,"%d",operand2_dim[1]);
    	    				strcat(mulDim,tmp);
    	    				strcat(mulDim,"]");
    	    				push(stack, mulDim);
    	    			}
    	    			else{
    	    				printf("PrdVector-Matrix Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		}
    	    		else if(operand1[0]=='[' && operand2[0]=='[' && !contains(operand1,',') && !contains(operand2,',')){

    	    			int operand2_dim=vector_dim_returner(operand2);
    	    			int operand1_dim=vector_dim_returner(operand1);
    	    			if(operand2_dim==operand1_dim && operand1_dim==1){
    	    				push(stack, operand1);
    	    			}
    	    			else{
    	    				printf("PrdVector-Vector Dimension Mismatch\n");
    	    				return "\0";
    	    			}
    	    		}
    	    		else if(is_integer(operand1) &&(is_integer(operand2)|| operand2[0]=='[')){
    	    			push(stack, operand2);
    	    		}
    	    		else if(is_integer(operand2) &&(is_integer(operand1)|| operand1[0]=='[')){
    	    			push(stack, operand1);
    	    		}
    	    		else{
    	    			printf("**** OPERATION ERROR!\n");
    	    			return "\0";
    	    		}
    	    	}
    	    	
    		    
    	    
    	}
    	i++;
    }
    //printf("Peek: %s\n", peek(stack));
    return peek(stack);
}

int contains(char* str,char ch){
	int index=0;
	while(str[index]!='\0'){
		if(str[index]==ch){
			return 1;
		}
		index++;
	}
	return 0;
	
}

int* matrix_dim_returner(char* str1){
	int* dimArray=(int*)malloc(sizeof(int)*2);
	char array1[100];
	memset(array1, '\0', sizeof(array1));
	char array2[100];
	memset(array2, '\0', sizeof(array2));
	int index=1;
	while(str1[index]!=','){
		array1[index-1]=str1[index];
		index++;
	}
	index++;
	int index2=index;
	while(str1[index]!=']'){
		array2[index-index2]  = str1[index];
		index++;
	}
	sscanf(array1, "%d", dimArray);
	sscanf(array2, "%d", dimArray + 1);
	return dimArray;
}
int vector_dim_returner(char* str1){
	char array1[100];
	int dimension;
	memset(array1, '\0', sizeof(array1));
	int index=1;
	while(str1[index]!=']'){
		array1[index-1]=str1[index];
		index++;
	}
	
	sscanf(array1, "%d", &dimension);
	return dimension;
}

