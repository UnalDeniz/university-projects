#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern char *inputName;

void split(char**** lexemes){
	FILE *input = fopen(inputName, "r");
	int lineCount = 0;
	int wordCount = 0;
	int index = 0;
	char c;

	while(1){
		//taking the input character by character until the end of file
		c = fgetc(input);
		if(c == EOF){
			break;
		}
		//allocating space for new lines and words
		if((*lexemes)[lineCount] == NULL){
			(*lexemes)[lineCount] = malloc(sizeof(char*) * 1024);
		}
		if((*lexemes)[lineCount][wordCount] == NULL){
			(*lexemes)[lineCount][wordCount] = malloc(sizeof(char) * 256);
		}
		if(c == ' ' || c=='\t'){
			//whenever the character is whitespace or tab continues from the new word (if it is not start of the line or word already)
			if(!(wordCount == 0 && index == 0) && (*lexemes)[lineCount][wordCount][0]!='\0'){
				wordCount++;
				(*lexemes)[lineCount][wordCount] = malloc(sizeof(char) * 256);
				index = 0;
			}
			continue;
		}
		if(c=='(' || c==')' || c=='{' || c=='}' || c=='[' || c==']' || c==',' || c==':' || c=='*' || c=='+' || c=='-' || c=='='){
			//whenever the character is a binary opertion or a paranthesis continues from the new word (if it is not start of the line or word already)
			if(!(wordCount == 0 && index == 0) && (*lexemes)[lineCount][wordCount][0] != '\0'){
				wordCount++;
			}
			(*lexemes)[lineCount][wordCount] = malloc(sizeof(char) * 256);
			index = 0;
			(*lexemes)[lineCount][wordCount][index] = c;
			continue;
		}
		if(c == '\n'){
			if(index == 0 && wordCount == 0){
				lineCount++;
				continue;
			}
			//if not already at the start of a new word continues from the next word
			if((*lexemes)[lineCount][wordCount][0] != '\0'){
				wordCount++;
				(*lexemes)[lineCount][wordCount] = malloc(sizeof(char) * 256);
			}
			//ends the line with newline character and continues from the first word of the next line	
			(*lexemes)[lineCount][wordCount][0] = '\n';
			index = 0;
			wordCount = 0;
			lineCount++;
			wordCount = 0;
			continue;
		}
		if(c == '#'){
			//if the comment character is detected skips the rest of the line
			while(c != '\n'){
				c = fgetc(input);
			}
			//if the comment character is at the start of the line completely skips the line without newline character
			if(index == 0 && wordCount == 0){
				lineCount++;
				continue;
			}
			//if not already at the start of a new word continues from the next word
			if((*lexemes)[lineCount][wordCount][0] != '\0'){
				wordCount++;
				(*lexemes)[lineCount][wordCount] = malloc(sizeof(char) * 256);
			}
			//ends the line with newline character and continues from the first word of the next line	
			(*lexemes)[lineCount][wordCount][0] = '\n';
			index = 0;
			wordCount = 0;
			lineCount++;
			wordCount = 0;
			continue;

		}
		if(wordCount != 0){
			//if the character is not a special character (it is a number or a letter) and the previous character was a special one starts from a new word
			char t = (*lexemes)[lineCount][wordCount][0];
			if(t==' ' || t=='\t' || t=='(' || t==')' || t=='{' || t=='}' || t=='[' || t==']' || t==',' || t==':' || t=='*' || t=='+' || t=='-' || t=='='){
				wordCount++;
				(*lexemes)[lineCount][wordCount] = malloc(256*sizeof(char));
			}
		}
		(*lexemes)[lineCount][wordCount][index] = c;
		index++;	
	}
	lineCount = 0;
	while((*lexemes)[lineCount] != NULL){
		wordCount = 0;
		while((*lexemes)[lineCount][wordCount] != NULL){
			printf("--%s", (*lexemes)[lineCount][wordCount]);
			wordCount++;
		}
		lineCount++;
	}
	fclose(input);
}
