#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#define MAX_INPUT 1024
//ESTAS TRABAJANDO AHORA EN EL USER INPUT

typedef struct {
    int size;        
    int capacity;       
    char** buffer;   
} string_queue;

//add an element
void enqueue(string_queue* q, char* str){
    if(q->size == q->capacity){ //in case it is not big enough
        q->capacity *= 2;
        q->buffer = realloc(q->buffer, q->capacity * sizeof(char*));
    }
    q->buffer[q->size++] = str;
}

//remove an element
char* dequeue(string_queue* q){
    if(q->size == 0) return NULL;

    char* dequeued_string = q->buffer[0];

    for(int i = 1; i < q->size; i++){
        q->buffer[i - 1] = q->buffer[i];
    }

    q->size--;
    return dequeued_string;
}

//gather user input
void user_input(string_queue* q){
    char buffer[MAX_INPUT];
    fgets(buffer, sizeof(buffer), stdin); //get input

    char* word = strtok(buffer, " "); //get each word separated by " "
    while(word != NULL){ //traverse the string until <-
        enqueue(q, strdup(word));
        word = strtok(NULL, " ");
    }
}


//my function
int my_scanf(const char* format, ...){
    //static queue
    static string_queue input_buffer;
if(input_buffer.capacity == 0){
        input_buffer.capacity = 10;
        input_buffer.size = 0;
        input_buffer.buffer = malloc(input_buffer.capacity * sizeof(char*));
    }

    //get the variable variables ready
    va_list variables;
    va_start(variables, format);
    
    //Format with what we have
    for(int i = 0; format[i] != '\0'; i++){
        if(format[i] == '%'){
            //IN CASE WE RAN OUT OF ELEMENTS IN THE QUEUE
            if(input_buffer.size == 0) user_input(&input_buffer);
            for(int i = 0; i < input_buffer.size; i++){
                printf("%s\n", input_buffer.buffer[i]);
            }

            // char format_specifier = format[i+1];
            // switch(format_specifier){
            //     case 'd':
            //         printf("Found a decimal");
            //         break;
            // }
            // i++; //skip the letter
        }
    }

    va_end(variables);

    return 0;
}

int main(){
    int a;
    int b;
    my_scanf("%d %d", &a, &b);

    return 0;
}