#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int top;
    int size;
    char* elements;
}Stack;

Stack create(int initial_size){
    Stack new_stack;
    char* array = malloc(initial_size * sizeof(char));
    new_stack.elements = array;
    new_stack.size = initial_size;
    new_stack.top = -1;
    return new_stack;
}

void push(Stack* stack, char element){
    if ((stack->top + 1) == stack->size) {
        stack->size *= 2;
        stack->elements = realloc(stack->elements, stack->size * sizeof(char));
    }
    stack->elements[++(stack->top)] = element;
}

int is_empty(Stack* stack) {return (stack->top == -1) ? 1 : 0;}

int is_full(Stack* stack) {return (stack->size == (stack->top + 1)) ? 1 : 0;}

char pop(Stack* stack){
    if(is_empty(stack)){
        printf("ERROR: Pop from empty stack.\n");
        exit(1);
    }
    return stack->elements[(stack->top)--];
}

char peek(Stack* stack) {
    if(is_empty(stack)){
        printf("ERROR: Peek from empty stack.\n");
        exit(1);
    }
    return stack->elements[stack->top];
}

char* check_balanced(Stack* stack, char* word){
    int n = strlen(word);
    
    for(int i = 0; i < n; i++){
        switch(word[i]){
            case '(':
                push(stack, '(');
                break;
            case '[':
                push(stack, '[');
                break;
            case '{':
                push(stack, '{');
                break;
            case ')':
                if(!is_empty(stack) && peek(stack) == '(') pop(stack);
                else push(stack, 'E');
                break;
            case ']':
                if(!is_empty(stack) && peek(stack) == '[') pop(stack);
                else push(stack, 'E');
                break;
            case '}':
                if(!is_empty(stack) && peek(stack) == '{') pop(stack);
                else push(stack, 'E');
                break;
        }
    }
    if(is_empty(stack) == 1) return "balanced";
    else return "unbalanced";
}

int main(){

    Stack stack = create(10);

    //FUNCTIONALITY
    //==============================================

    printf("%s",check_balanced(&stack, "[[]]"));

    //==============================================

    free(stack.elements);
    return 0;
}