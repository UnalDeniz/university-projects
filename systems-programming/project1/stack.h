// C program to evaluate value of a postfix expression
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
 
// Stack type
struct Stack
{
    int top;
    unsigned capacity;
    char** array;
};
 
// Stack Operations
struct Stack* createStack( unsigned capacity )
{
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
 
    if (!stack) return NULL;
 
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char**) malloc(stack->capacity * 256);
    if (!stack->array) return NULL;
 
    return stack;
}
 
int isEmpty(struct Stack* stack)
{
    return stack->top == -1 ;
}
 
char *peek(struct Stack* stack)
{
    return stack->array[stack->top];
}
 
char *pop(struct Stack* stack)
{
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return "POP ERROR STACK!";
}
 
void push(struct Stack* stack, char* op)
{
    stack->array[++stack->top] = op;
}
 
