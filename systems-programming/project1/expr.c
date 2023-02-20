#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKENS   100 
#define TOKENLENGTH 20  

extern char tokens[MAXTOKENS][TOKENLENGTH] ;
#define N  1000 

char str[N] ;
char prt[N] ; 
int  cur = 0 ; 
char lastStr[50];
int  expr(char *, char *) ;
int  term(char *, char *) ;
int  moreterms(char *, char *) ;
int  factor(char *, char *) ;
int  morefactors(char *, char *) ;
int  is_integer(char *) ; 
int is_Func(char *);
int funcs(char *, char *);
int is_Alpha(char *);
char* transpoze(char *);
char* stackSolver(char *, int);
int contains(char* str,char ch);
int vector_dim_returner(char* str1);
int* matrix_dim_returner(char* str1);
//int is_indiced_Mat(char* str1);
int is_indiced_Vec(char* str1);
int indicedVar(char* str1, char*);
char* indicerTwo(char *str, char *name);
char* indicerOne(char *str, char *name);
char* searcher(char *str);
char** exprSolver()
{
   
   int     numtokens ; 
   char    str[N]   ; 
   char	   prt[N]	;
   cur=0;
   
   // read the tokens 
   /*numtokens = 0 ; 
   while (scanf("%s",tokens[numtokens]) != EOF) {
      numtokens++ ; 
   } 
   sprintf(tokens[numtokens],"$") ;
   numtokens++ ; 
   */
   // parse the expression 
   //printf("%s ",tokens[0]);
   
   char **hrr = (char**)malloc(2*sizeof(char*));
   if(expr(str,prt)){

	   // BURALAR DEGİSECEK DAHA YENİ 10 Nisan
       strcpy(lastStr,stackSolver(str,1));
	   printf("\nlast_prt: %s\n",prt);
       printf("last_str %s\n",lastStr);
       hrr[1] = prt;
       hrr[0] = lastStr;
       return hrr;
   }
   else{
   	   printf("2... %s  ERRORR!!\n", str);
	hrr[0] = "\0";
	hrr[1] = "\0";
       return hrr;
   }
   /*
   printf("EXPR TRUE/FALSE: %d\n",expr(str,prt));

   

   strcpy(lastStr,stackSolver(str,1));
   printf("LAST STR %s\n", lastStr);
   printf("LAST PRT %s\n", prt);
   return lastStr; */
   return hrr ;
}

int expr(char *str, char *prt)
{

   char str1[N], str2[N], str3[N] ; 
   char prt1[N], prt2[N], prt3[N], prt4[N] ;
   
   str1[0] = str2[0] = str3[0]= '\0' ; 
   prt1[0] = prt2[0] = prt3[0]= prt4[0]='\0' ; 
   if (!  term(str2,prt2)) {
      return(0) ; 
   } 
   if (!  moreterms(str3,prt3)) {
      return(0) ; 

   }
   printf("Expr str2: %s\n", str2);
   printf("Expr str3: %s\n", str3);

   char str2_temp[N];
   char str3_temp[N];
   strcpy(str2_temp,str2);
   strcpy(str3_temp,str3);

   //TO THE C CODE
	if(str2[0]!='\0' && str3[0]!='\0'){
		int index=0;
		while(str3[index]!='+' && str3[index] !='-'){
			index++;
		}
		str1[0]=str3[index];
		prt1[0]=str3[index];
		str3[index]='\0';
		char stackResultOP1[N];
		strcpy(stackResultOP1,stackSolver(str2,1));
		if(strcmp(stackResultOP1,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		char stackResultOP2[N];
		strcpy(stackResultOP2,stackSolver(str3,1));
		if(strcmp(stackResultOP2,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		if(is_integer(stackResultOP1) && is_integer(stackResultOP2)){
			if(contains(prt1,'+')){
				strcpy(prt4,"sum( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				strcpy(prt,prt4);
			}
			else if(contains(prt1,'-')){
				strcpy(prt4,"sub( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				strcpy(prt,prt4);
			}
		}
		else{
			if(contains(prt1,'+')){
				strcpy(prt4,"summ( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				strcpy(prt,prt4);
			}
			else if(contains(prt1,'-')){
				strcpy(prt4,"subm( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				strcpy(prt,prt4);
			}
			
		}
		char stackResultOP3[N];
		strcat(str2_temp,str3_temp); // Expr'a alttan gelen term ve moreterms(term +) yı birlestirip sonra stack e sokup yukarı yolluyoruz.
		strcpy(stackResultOP3,stackSolver(str2_temp,1));
		if(strcmp(stackResultOP3,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		strcat(stackResultOP3," ");
		
		strcpy(str,stackResultOP3);
	
	}
	else {
		strcat(str2_temp,str3_temp) ;
   		strcpy(str,str2_temp) ; 
		strcat(prt2,prt3) ;
   		strcat(prt2, prt1);
   		strcpy(prt,prt2) ; 
	}


   
   return(1) ;  
}

int term(char *str, char *prt)
{
	
   char str1[N], str2[N], str3[N] ; 
   char prt1[N], prt2[N], prt3[N], prt4[N] ;
   
   str1[0] = str2[0] = str3[0]= '\0' ; 
   prt1[0] = prt2[0] = prt3[0]= prt4[0]='\0' ; 
   if (!  factor(str2,prt2)) {
	   
      return(0) ; 
   } 
   
   if (!  morefactors(str3,prt3)) {
      return(0) ; 
   }
   printf("Terms str2: %s\n", str2);
	printf("Terms str3: %s\n", str3);
   char str2_temp[N];
   char str3_temp[N];
   strcpy(str2_temp,str2);
   strcpy(str3_temp,str3);
   
	//TO THE C CODE
	if(str2[0]!='\0' && str3[0]!='\0'){
		
		int index=0;
		while(str3[index]!='*'){
			index++;
		}

		str1[0]=str3[index];
		prt1[0]=str3[index];
		str3[index]='\0';


		printf("InTerms str2: %s\n", str2);
		printf("InTerms str3: %s\n", str3);
		char stackResultOP1[N];
		
		strcpy(stackResultOP1,stackSolver(str2,1));
		if(strcmp(stackResultOP1,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		
		char stackResultOP2[N];
		strcpy(stackResultOP2,stackSolver(str3,1));
		if(strcmp(stackResultOP2,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		//printf("InTerms stack2: %d\n", is_integer(stackResultOP1));
		//printf("InTerms stack3: %s\n", stackResultOP2);
		if(is_integer(stackResultOP1) && is_integer(stackResultOP2)){
			strcpy(prt4,"product( ");
			strcat(prt4, prt2);
			strcat(prt4,", ");
			strcat(prt4, prt3);
			strcat(prt4, ") ");
			strcpy(prt,prt4); 
		}
		else if(is_integer(stackResultOP1) && !is_integer(stackResultOP2)){
			strcpy(prt4,"multim( ");
			strcat(prt4, prt2);
			strcat(prt4,", ");
			strcat(prt4, prt3);
			strcat(prt4, ") ");
			strcpy(prt,prt4);
		}
		else if(!is_integer(stackResultOP1) && is_integer(stackResultOP2)){
			strcpy(prt4,"multim( ");
			strcat(prt4, prt3);
			strcat(prt4,", ");
			strcat(prt4, prt2);
			strcat(prt4, ") ");
			strcpy(prt,prt4);

		}
		else{
			
			strcpy(prt4,"productm( ");
			strcat(prt4, prt2);
			strcat(prt4,", ");
			strcat(prt4, prt3);
			strcat(prt4, ") ");
			strcpy(prt,prt4);
		}
		char stackResultOP3[N];
		strcat(str2_temp,str3_temp); // Expr'a alttan gelen term ve moreterms(term +) yı birlestirip sonra stack e sokup yukarı yolluyoruz.
		strcpy(stackResultOP3,stackSolver(str2_temp,1));
		if(strcmp(stackResultOP3,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		strcat(stackResultOP3," ");
		
		strcpy(str,stackResultOP3);
	
	
	}
	else {
		strcat(str2_temp,str3_temp) ;
   		strcpy(str,str2_temp) ; 
		strcat(prt2,prt3) ;
   		strcat(prt2, prt1);
   		strcpy(prt,prt2) ; 
	}


   
   return(1) ;  
}

int moreterms(char *str, char *prt)
{
	char str1[N], str2[N], str3[N], str5[N]; 
	char prt1[N], prt2[N], prt3[N], prt4[N], prt5[N];

	str1[0] = str2[0] = str3[0] =str5[0]='\0' ; 
	prt1[0] = prt2[0] = prt3[0] = prt4[0]=prt5[0]='\0' ;

	if ( (strcmp(tokens[cur],"+") == 0 ) || (strcmp(tokens[cur],"-") == 0 ) ) {
		strcpy(str1,tokens[cur]) ; 
		strcat(str1," ") ; 
		strcpy(prt1,tokens[cur]) ; 
		strcat(prt1," ") ;
		cur++ ;  
		if (!  term(str2,prt2)) {
			return(0) ; 
		} 
		
		if (!  moreterms(str3,prt3)) {
			return(0) ; 
		}
	}
	printf("MoreTerms str2: %s\n", str2);
	printf("MoreTerms str3: %s\n", str3);
	char str2_temp[N];
   	char str3_temp[N];
   	strcpy(str2_temp,str2);
   	strcpy(str3_temp,str3);
	//TO THE C CODE
	if(str2[0]!='\0' && str3[0]!='\0'){
		
		int index=0;
		while(str3[index]!='+' && str3[index] !='-'){
			index++;
		}
		str5[0]=str3[index];
		prt5[0]=str3[index];
		str3[index]='\0';

		printf("InMoreTerms str2: %s\n", str2);
		printf("InMoreTerms str3: %s\n", str3);
		char stackResultOP1[N];
		strcpy(stackResultOP1,stackSolver(str2,1));
		if(strcmp(stackResultOP1,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		char stackResultOP2[N];
		strcpy(stackResultOP2,stackSolver(str3,1));
		if(strcmp(stackResultOP2,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		if(is_integer(stackResultOP1) && is_integer(stackResultOP2)){
			if(contains(prt5,'+')){
				strcpy(prt4,"sum( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				//strcat(prt4,prt1);
				//strcat(prt4," ");
				strcpy(prt,prt4);
			}
			else if(contains(prt5,'-')){
				strcpy(prt4,"sub( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				//strcat(prt4,prt1);
				//strcat(prt4," ");
				strcpy(prt,prt4);
			}
		}
		else{
			if(contains(prt5,'+')){
				strcpy(prt4,"summ( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				//strcat(prt4,prt1);
				//strcat(prt4," ");
				strcpy(prt,prt4);
			}
			else if(contains(prt5,'-')){
				strcpy(prt4,"subm( ");
				strcat(prt4, prt2);
				strcat(prt4,", ");
				strcat(prt4, prt3);
				strcat(prt4, ") ");
				//strcat(prt4,prt1);
				//strcat(prt4," ");
				strcpy(prt,prt4);
			}
		}


		char stackResultOP3[N];
		strcat(str2_temp,str3_temp); // Expr'a alttan gelen term ve moreterms(term +) yı birlestirip sonra stack e sokup yukarı yolluyoruz.
		strcpy(stackResultOP3,stackSolver(str2_temp,1));
		if(strcmp(stackResultOP3,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		strcat(stackResultOP3," ");
		strcat(stackResultOP3,str1);
		
		strcpy(str,stackResultOP3);
	
	}
	else {
		
		strcat(str2_temp,str3_temp) ; 
		strcpy(str,str2_temp) ;	
   		strcpy(prt,prt2) ;
		
	}
	

	
	return(1) ;  
}
int factor(char *str, char *prt)
{
   char str1[N] ;
   char str2[N] ;
   char str3[N] ;
   str1[0] = '\0' ; 
   str2[0] = '\0' ;
   str3[0] = '\0' ;	
   char prt1[N] ;
   char prt2[N] ;
   char prt3[N] ;
   prt1[0] = '\0' ; 
   prt2[0] = '\0' ;
   prt3[0] = '\0' ;	


    if ( is_integer(tokens[cur])  ) {
		printf("Integer %s\n",tokens[cur]);
       strcpy(str,tokens[cur]) ; 
       strcat(str," ") ; 
	   strcpy(prt,tokens[cur]) ; 
       strcat(prt," ") ; 
       cur++ ; 
       return(1) ; 
    } 

    else if ( strcmp(tokens[cur],"(") == 0 ) {
		printf("parantheses %s\n",tokens[cur]);
       cur++ ; 
       if ( ! expr(str1,prt1) ) {
          return(0) ;    
       }
       if ( strcmp(tokens[cur],")") !=0  ) { 
          printf("Error: expecting paranthesis\n") ; 
          return(0) ;
       }
       strcpy(str, str1);
	   strcpy(prt,prt1);
       cur++ ; 
       return(1) ; 
    }

    else if (is_Func(tokens[cur])) {
		printf("Function %s\n",tokens[cur]);
		if(!funcs(str2,prt2)){
			return(0);
		}
		strcpy(str, str2);
		strcpy(prt,prt2);
		return(1);
	}
	/*
	else if(is_indiced_Mat(tokens[cur])){

		if(!indicedVar(str3)){
			return(0);
		}
		strcpy(str,str3);
	
		return(1);
	}*/
    else if(is_indiced_Vec(tokens[cur])){
		printf("INDICED VEC %s\n",tokens[cur]);
		if(!indicedVar(str3,prt3)){
			return(0);
		}

		strcpy(str,str3);
		strcpy(prt,prt3);
	
		return(1);
		
	}
    else if(is_Alpha(tokens[cur])){
		printf("Variable %s\n",tokens[cur]);
    	strcpy(str,tokens[cur]);
    	strcat(str," ");
		strcpy(prt,tokens[cur]);
    	strcat(prt," ");
    	cur++;
    	return(1);
    }

    
    printf("Error: expecting factor\n") ; 
    return(0) ; 
}





int morefactors(char *str, char *prt)
{
	
	char str1[N], str2[N], str3[N] , str5[N]; 
	char prt1[N], prt2[N], prt3[N], prt4[N] , prt5[N] ; 

	str1[0] = str2[0] = str3[0] = str[5] ='\0' ; 
	prt1[0] = prt2[0] = prt3[0] = prt4[0]=prt5[N]='\0' ;

	if ( (strcmp(tokens[cur],"*") == 0 ) ) {
		strcpy(str1,tokens[cur]) ; 
		strcat(str1," ") ; 
		strcpy(prt1,tokens[cur]) ; 
		strcat(prt1," ") ; 
		cur++ ;  
		if (!  factor(str2,prt2)) {
			return(0) ; 
		} 
		if (!  morefactors(str3,prt3)) {
			return(0) ; 
		}
	} 
	
	char str2_temp[N];
   	char str3_temp[N];
   	strcpy(str2_temp,str2);
   	strcpy(str3_temp,str3);
	   printf("MoreFactors str2: %s\n", str2);
	printf("MoreFactors str3: %s\n", str3);
	//TO THE C CODE
	if(str2[0]!='\0' && str3[0]!='\0'){
		int index=0;
		while(str3[index]!='*'){
			index++;
		}
		str5[0]=str3[index];
		prt5[0]=str3[index];
		str3[index]='\0';

		printf("InMoreFactors str2: %s\n", str2);
		printf("InMoreFactors str3: %s\n", str3);
		char stackResultOP1[N];
		strcpy(stackResultOP1,stackSolver(str2,1));
		if(strcmp(stackResultOP1,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		char stackResultOP2[N];
		strcpy(stackResultOP2,stackSolver(str3,1));
		if(strcmp(stackResultOP2,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		if(is_integer(stackResultOP1) && is_integer(stackResultOP2)){
			strcpy(prt4,"products( ");
			strcat(prt4, prt2);
			strcat(prt4,", ");
			strcat(prt4, prt3);
			strcat(prt4, ") ");
			//strcat(prt4,prt1);
			//strcat(prt4," ");
			strcpy(prt,prt4); 
		}
		else if(is_integer(stackResultOP1) && !is_integer(stackResultOP2)){
			strcpy(prt4,"multim( ");
			strcat(prt4, prt2);
			strcat(prt4,", ");
			strcat(prt4, prt3);
			strcat(prt4, ") ");
			//strcat(prt4,prt1);
			//strcat(prt4," ");
			strcpy(prt,prt4);
		}
		else if(!is_integer(stackResultOP1) && is_integer(stackResultOP2)){

			strcpy(prt4,"multim( ");
			strcat(prt4, prt3);
			strcat(prt4,", ");
			strcat(prt4, prt2);
			strcat(prt4, ") ");
			//strcat(prt4,prt1);
			//strcat(prt4," ");
			strcpy(prt,prt4);

		}
		else{
			
			strcpy(prt4,"productm( ");
			strcat(prt4, prt2);
			strcat(prt4,", ");
			strcat(prt4, prt3);
			strcat(prt4, ") ");
			//strcat(prt4,prt1);
			//strcat(prt4," ");
			strcpy(prt,prt4);
		}
		strcat(str2_temp,str3_temp);
		printf("STR TEMP TOTAL %s\n", str2_temp);
		
		char stackResultOP3[N];
		strcpy(stackResultOP3,stackSolver(str2_temp,1));
		if(strcmp(stackResultOP3,"\0")==0){
			printf("Stack Solver Error\n");
			return(0);
		}
		strcat(stackResultOP3," ");

		strcat(stackResultOP3,str1);
		strcpy(str,stackResultOP3);
		

	
	}
	
	else{
		strcpy(prt,prt2);
		strcat(str2_temp,str3_temp) ; 

		strcat(str2_temp,str1) ;

		strcpy(str,str2_temp) ; 
	}
	
	
	return(1) ;  
}
int funcs(char *str, char *prt)
{
	//This is for syntax + dimension control
    char str1[N];
    str1[0] = '\0' ;
	//Bottom strs are created for choose
	char str2[N];
    str2[0] = '\0' ;
	char str3[N];
    str3[0] = '\0' ;
	char str4[N];
    str4[0] = '\0' ;
	

	//These char arrays are for printing
	char prt1[N] ; //Variable for expr
    prt1[0] = '\0' ;
    char prt2[N];
	prt2[0] = '\0' ;
	//Bottom prts are created for choose
	char prt3[N];
	prt3[0] = '\0' ;
	char prt4[N];
	prt4[0] = '\0' ;
	char prt5[N]; // For printing choose
	prt5[0] = '\0' ;
	
   	if(strcmp(tokens[cur],"tr")==0){
   		cur++;
    	
    	if(strcmp(tokens[cur],"(")==0){
    	    cur++;
    	}
    	else{
    	    printf("Tr Paranthese Issue\n");
    	    return(0);
    	}
        if(!expr(str1,prt1)){
            return(0);
        }
        //printf("str1 %s\n", str1);
        char stackResult[N];
       
        strcpy(stackResult,stackSolver(str1,1));
        if(strcmp(stackResult,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
        //printf("Stack Result %s \n", stackResult);
        //BURADA str1 i STACK E SOKUP SONUCUNU dim OLARAK CIKARMAK LAZIM:
        if(strcmp(tokens[cur],")")==0){
            
            cur++;
        }
        else{
            printf("Tr Expecting Paranthese Issue\n");
    	    return(0);
        }

		//TO THE C CODE!!!
		if(!contains(stackResult,',')){
			//VECTOR PRINT
			if(stackResult[0]=='['){
				strcpy(prt2,"trm( ");
				strcat(prt2, prt1);
				strcat(prt2, ") ");
			}
			//SCALAR PRINT
			else{
				strcpy(prt2,"tr( ");
				strcat(prt2, prt1);
				strcat(prt2, ") ");
			}
		}
		// MATRIX  PRINT
		else{
			strcpy(prt2,"trm( ");
			strcat(prt2, prt1);
			strcat(prt2, ") ");
		}
		
		strcpy(prt,prt2);
		//TO THE C CODE!!!


        char Result[N];// MAYBE THIS CAN CREATE A PROBLEM

        strcpy(Result,transpoze(stackResult));
        strcat(Result," ");
        strcpy(str,Result);

        //free(Result);
        
    	return(1);   
   	}
   	else if(strcmp(tokens[cur],"sqrt")==0){
   		cur++;
    	
    	if(strcmp(tokens[cur],"(")==0){
    	    cur++;
    	}
    	else{
    	    printf("Sqrt Paranthese Issue\n");
    	    return(0);
    	}
        if(!expr(str1,prt1)){
            return(0);
        }
		printf("SQRT: %s\n",str1);
        char stackResult[N];
       
        strcpy(stackResult,stackSolver(str1,1));
        if(strcmp(stackResult,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
		printf("SQRT: %s\n",str1);
        if(strcmp(tokens[cur],")")==0){
            
            cur++;
        }
        else{
            printf("Sqrt Expecting Paranthese Issue\n");
    	    return(0);
        }
printf("SQRT: %s\n",str1);
		//TO THE C CODE!!!
		if(!contains(stackResult,',')){
			//VECTOR PRINT
			if(stackResult[0]=='['){
				strcpy(prt2,"sqrtm( ");
				strcat(prt2, prt1);
				strcat(prt2, ") ");
			}
			//SCALAR PRINT
			else{
				strcpy(prt2,"sqrt( ");
				strcat(prt2, prt1);
				strcat(prt2, ") ");
			}
		}
		// MATRIX  PRINT
		else{
			strcpy(prt2,"sqrtm( ");
			strcat(prt2, prt1);
			strcat(prt2, ") ");
		}
		printf("SQRT: %s\n",str1);
		printf("SQRT: %s\n",str1);
		strcpy(prt,prt2);
		printf("SQRT: %s\n",str1);
		//TO THE C CODE!!!
        char Result[N];
		printf("SQRT: %s\n",str1);
        
        strcpy(Result,stackResult);
        strcat(Result," ");
        strcpy(str,Result);
		
    	return(1);   
   	}

	   //CHOOSE
	else if(strcmp(tokens[cur],"choose")==0){
		cur++;
    	
    	if(strcmp(tokens[cur],"(")==0){
    	    cur++;
    	}
    	else{
    	    printf("Choose Paranthese Issue\n");
    	    return(0);
    	}
        if(!expr(str1,prt1)){
            return(0);
        }
		// Look that expression's result is a scalar or not!
		char probDim[N];  
		memset(probDim,'\0',sizeof(probDim));    
        strcpy(probDim,stackSolver(str1,1));
		if(strcmp(probDim,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
		if(!is_integer(probDim)){
			printf("Choose function 1st is not scalar\n");
			return(0);
		}	

		if((strcmp(tokens[cur],","))==0){
			cur++;
		}
		else{
			printf("Expected Comma is not HERE!");
		}
		if(!expr(str2,prt2)){
			return(0);
		}
		// Look that expression's result is a scalar or not!
		   
		memset(probDim,'\0',sizeof(probDim));     
        strcpy(probDim,stackSolver(str2,1));
		if(strcmp(probDim,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
		if(!is_integer(probDim)){
			printf("Choose function 2nd is not scalar\n");
			return(0);
		}	
		if((strcmp(tokens[cur],","))==0){
			cur++;
		}
		else{
			printf("Expected Comma is not HERE!");
		}
		if(!expr(str3,prt3)){
			return(0);
		}
		// Look that expression's result is a scalar or not!
		memset(probDim,'\0',sizeof(probDim));        
        strcpy(probDim,stackSolver(str3,1));
		if(strcmp(probDim,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
		if(!is_integer(probDim)){
			printf("Choose function 3rd is not scalar\n");
			return(0);
		}	
		if((strcmp(tokens[cur],","))==0){
			cur++;
		}
		else{
			printf("Expected Comma is not HERE!");
		}
		if(!expr(str4,prt4)){
			return(0);
		}
		// Look that expression's result is a scalar or not!
		memset(probDim,'\0',sizeof(probDim));       
        strcpy(probDim,stackSolver(str4,1));
		if(strcmp(probDim,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
		if(!is_integer(probDim)){
			printf("Choose function 4th is not scalar\n");
			return(0);
		}	

        if(strcmp(tokens[cur],")")==0){
            
            cur++;
        }
        else{
            printf("Choose Expecting Paranthese Issue\n");
    	    return(0);
        }
		strcpy(prt5,"choose( ");
		strcat(prt5, prt1);
		strcat(prt5,", ");
		strcat(prt5,prt2);
		strcat(prt5,", ");
		strcat(prt5,prt3);
		strcat(prt5,", ");
		strcat(prt5,prt4);
		strcat(prt5,") ");
		strcpy(prt,prt5);


		strcpy(str,"1 ");

		return(1);

	}
   	
   
    printf("Function Error!");
    return 0;
}
int indicedVar(char *str, char *prt){
	char str1[N];
	str1[0] = '\0';
    char str2[N];
	str2[0] = '\0';
    char str3[N];
	str3[0]='\0';
	char prt1[N];
	prt1[0] = '\0';
    char prt2[N];
	prt2[0] = '\0';
    char prt3[N];
	prt3[0]='\0';

    char result[N];
	result[0]='\0';
    char name[N];
	name[0]='\0';
	char *temp;
    
    
    
    
    
	if(is_Alpha(tokens[cur])){
		strcpy(name, tokens[cur]);
		cur++;
		
	}
	if(strcmp(tokens[cur],"[")==0){
		cur++;
	}
	else{
		printf("Indiced Variable Paranthese Issue\n");
		return(0);
	}
	if(!expr(str1,prt1)){
		return(0);
	}
	// Look that expression's result is a scalar or not!
	char* probDim1=stackSolver(str1,1);
	if(strcmp(probDim1,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
	if(!is_integer(probDim1)){
		printf("Matrix dim inside is not scalar!\n");
		return(0);
	}	
	if(strcmp(tokens[cur],",")==0){
		cur++;
		if(!expr(str2,prt2)){
			return(0);
		}
		// Look that expression's result is a scalar or not!
		char* probDim2=stackSolver(str2,1);
		if(strcmp(probDim2,"\0")==0){
        	printf("Stack Solver Error\n");
        	return(0);
        }
		if(!is_integer(probDim2)){
			printf("Matrix dim inside is not scalar!\n");
			return(0);
		}
		
		if(strcmp(tokens[cur],"]")==0){
			cur++;
		}
		else{
			printf("Indiced Variable Expecting Paranthese\n");
			return(0);
		}
		strcpy(str3,"[");
		strcat(str3,probDim1);
		strcat(str3,",");
		strcat(str3,probDim2);
		strcat(str3,"]");
		
		temp=indicerTwo(str3, name);
		if(strcmp(temp,"\0")==0){
			printf("Inducer Error!\n");
			return(0);
		}
		strcpy(result, temp);
		strcat(result," ");


		//TO THE C CODE
		strcpy(prt3,name);
		strcat(prt3,".values");
		strcat(prt3,"[(int)");
		strcat(prt3, prt1);
		strcat(prt3,"][(int)");
		strcat(prt3, prt2);
		strcat(prt3,"]");
		//TO THE C CODE
	}
	else{
		if(strcmp(tokens[cur],"]")==0){
			cur++;
		}
		else{
			printf("Indiced Variable Expecting Paranthese\n");
			return(0);
		}
		
		//parantezleri ekle
		strcpy(str3,"[");
		strcat(str3,probDim1);
		strcat(str3,"]");
		temp=indicerOne(str3, name);
		if(strcmp(temp,"\0")==0){
			printf("Inducer Error!\n");
			return(0);
		}
		strcpy(result, temp);
		strcat(result," ");


		//TO THE C CODE
		strcpy(prt3,name);
		strcat(prt3,".values");
		strcat(prt3,"[(int) ");
		strcat(prt3, prt1);
		strcat(prt3,"][1]");
		//TO THE C CODE


	}
	strcpy(str, result);
	strcpy(prt, prt3);					
	return(1);
}


char* transpoze(char *str){
	
	char* result =(char*)malloc(sizeof(char)*N);
	strcpy(result,"[");
    if(!contains(str,',')){
    	//VECTOR TRANSPOZE
		if(str[0]=='['){
			int operand_temp=vector_dim_returner(str);
			char operand[30];
			sprintf(operand,"%d", operand_temp);
			strcat(result,"1,");
			strcat(result, operand);
			strcat(result, "]");
		}
		//SCALAR TRANSPOZE
		else{
			//no need to something
		}
	}
    // MATRIX  TRANSPOZE
	else{
		int* operands_temp=matrix_dim_returner(str);

		char operand1[30];
		char operand2[30];
		sprintf(operand1,"%d", operands_temp[0]);
		sprintf(operand2,"%d", operands_temp[1]);
		strcat(result, operand2);
		strcat(result, ",");
		strcat(result, operand1);
		strcat(result, "]");
		
	}

    return result;
 ///YAZACAM
}


char* indicerOne(char *str, char *name){

	// Both IndicerOne and Two doesnt return actual scalar value just returns 1 always.
	int operand;
	int indice;
	char* dimension=searcher(name);
	if(strcmp(dimension,"-1")==0){
		printf("No Element Found\n");
		return "\0";
	}

	//Check whether this is matrix or not

	if(!contains(dimension,',')){

		if(dimension[0]=='['){

		//These functions work because [3] they return the integer inside.
			operand=vector_dim_returner(dimension);
			indice=vector_dim_returner(str);
			if(!(indice<=operand)){
				printf("Vector Indice surpasses the dimension\n");
				return "\0";
			}
			return "1";
		}
		else{
			printf("Error! IT IS A SCALAR FOR INDICING\n");
			return "\0";
		}
				
	}
	
	//If it is matrix then compare double indice with dimension
	else{
/*
		int* operands=matrix_dim_returner(dimension);
		indice= vector_dim_returner(str);
		if(!(indice<= operands[0])){
			printf("MATRIX Indice surpasses the dimensions\n");
			return "\0";
		}
		strcpy(result, dimension);
		result[1]='1';

		return result;
		*/
		printf("ERROR! Trying to reach row of a matrix!!");
		return "\0";
		
	}

	
	
}

char* indicerTwo(char *str, char *name){
	
	int* operands;
	int* indices;
	char* dimension=searcher(name);
	if(strcmp(dimension,"-1")==0){
		printf("No Element Found\n");
		return "\0";
	}
	//Check whether this is matrix or not
	if(!contains(dimension,',')){
		printf("Not matrix double indice ERROR!\n");
		return "\0";
	}
	//If it is matrix then compare double indice with dimension
	operands=matrix_dim_returner(dimension);
	indices= matrix_dim_returner(str);
	if(!(indices[0]<= operands[0] && indices[1]<= operands[1])){
		printf("MATRIX Indice surpasses the dimensions\n");
		return "\0";
	}
	
	return "1";
}




/*

int is_indiced_Mat(char *token){

	int indexcur=cur;
	int index2cur=cur;
	if(isalpha(token[0])||token[0]=='_'){

		indexcur++;
   		while(tokens[indexcur][0]!='[' && tokens[indexcur][0]!='\0'){
   			indexcur++;
   		}
   		index2cur=indexcur;
   		while(tokens[indexcur][0]!=',' && tokens[indexcur][0]!='\0'){
   			indexcur++;
   		}
   		
   		if(tokens[indexcur][0]==',' && tokens[index2cur][0]=='['){
   			return 1;
   		}
   	}

   	return 0;	


}
*/
int is_indiced_Vec(char *token){

	int indexcur=cur;
	indexcur++;
	if(isalpha(token[0])||token[0]=='_'){
   		while(tokens[indexcur][0]!='[' && tokens[indexcur][0]!='\0'){
   			indexcur++;
   		}
   	
   		if(tokens[indexcur][0]=='['){
   			return 1;
   		}
   	}
   	return 0;
}
int is_integer(char *token) 
{
    int isnumber = 1 ;
    char *q ; 

    for(q = token ; *q != '\0' ; q++) {
        isnumber = isnumber && isdigit(*q) ;
    }

    return(isnumber) ; 
}    
int is_Func(char *token)
{
    if(strcmp(token,"choose")==0 || strcmp(token,"tr")==0 || strcmp(token,"sqrt")==0)
    {
    	return 1;
    }
    return 0;
}
int is_Alpha(char *token){
   if(isalpha(token[0])||token[0]=='_'){
   	return 1;
   }
   return 0;
}




