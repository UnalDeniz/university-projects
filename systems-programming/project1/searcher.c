#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


extern int vectorDimensions[1024];
extern char vectors[1024][128];
extern char scalars[1024][128];
extern char matrixArray[1024][128];
extern int matrixDimensions[2048];



char newVector[40];
char newMatrix[40];

char* searcher(char *str);

/*
int main(){
   char ptr[40];
   strcpy(ptr,searcher("abs"));
   printf("%s",ptr);
}

*/




char* searcher(char *str){  
	memset(newMatrix, '\0', sizeof(newMatrix));
	memset(newVector, '\0', sizeof(newVector));
   /*
    int vectorDimensions[]={4,4,6,7,8,9};
    char vectors[][100]={"y","x","cd","de","ef","gh"};
    int matrixDimensions[]={4,4,2,3};
    char matrixArray[][100]={"A","B"};
    char scalars[][100]={"abs","asdj"};
    */
    int index1=0;
    char vector[40];
    memset(vector, '\0', sizeof(vector));
	
    strcpy(vector,"[");
    char matrix[40];
     memset(matrix, '\0', sizeof(matrix));
    strcpy(matrix,"[");
    char integer1[40];
    char integer2[40];
   
    while(scalars[index1][0]!='\0'){
    	if(strcmp(scalars[index1],str)==0){ 
           printf("SEARCHER %s\n", str);
           printf("SCALARS[INDEX] %s\n", scalars[index1]);
           return "1";
    	}
		index1++;
    }   
    index1=0;
    while(vectors[index1][0]!='\0'){
    	if(strcmp(vectors[index1],str)==0){
    	   
    	   sprintf(integer1,"%d", vectorDimensions[index1]);
    	  
    	   strcat(vector,integer1);
    	   
    	   vector[strlen(vector)]=']';
			
    	   strcpy(newVector,vector);
           return newVector;
    	}
		index1++;
    }
     
    index1=0;
    matrix[0]='[';
    while(matrixArray[index1][0]!='\0'){
        
    	if(strcmp(matrixArray[index1],str)==0){
    	   sprintf(integer1,"%d",matrixDimensions[2*index1]);
    	   sprintf(integer2,"%d",matrixDimensions[2*index1+1]);
    	   strcat(matrix,integer1);
    	   matrix[strlen(matrix)]=',';
    	   strcat(matrix,integer2);
    	   matrix[strlen(matrix)]=']';
           //char *newMatrix = (char*)malloc(sizeof(char)*strlen(matrix));
   	   //char newMatrix[strlen(matrix)];
  	   strcpy(newMatrix,matrix);
    	   return newMatrix;
    	}
    	index1++;
    }
    return "-1";
   
}
