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
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline

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
    for(int i = 0; i <= strlen(format); i++){
        if(format[i] == '%'){
            //IN CASE WE RAN OUT OF ELEMENTS IN THE QUEUE
            if(input_buffer.size == 0) user_input(&input_buffer);
            char format_specifier = format[i+1];
            switch (format_specifier) {
                case 'h':
                    if (format[i + 2] == 'd') {
                        short* val = va_arg(variables, short*);
                        char* token = dequeue(&input_buffer);
                        if (!token) return -1;
                        *val = (short) strtol(token, NULL, 10);
                        i += 2;
                        break;
                    } else if (format[i + 2] == 'h' && format[i + 3] == 'd') {
                        signed char* val = va_arg(variables, signed char*);
                        char* token = dequeue(&input_buffer);
                        if (!token) return -1;
                        *val = (signed char) strtol(token, NULL, 10);
                        i += 3;
                        break;
                    }
                    break;
            
                case 'd': {
                    int* val = va_arg(variables, int*);
                    char* token = dequeue(&input_buffer);
                    if (!token) return -1;
                    *val = (int) strtol(token, NULL, 10);
                    break;
                }
            
                case 'l':
                    if (format[i + 2] == 'd') {
                        long* val = va_arg(variables, long*);
                        char* token = dequeue(&input_buffer);
                        if (!token) return -1;
                        *val = strtol(token, NULL, 10);
                        i += 2;
                        break;
                    } else if (format[i + 2] == 'f') {
                        double* val = va_arg(variables, double*);
                        char* token = dequeue(&input_buffer);
                        if (!token) return -1;
                        *val = strtod(token, NULL);
                        i += 2;
                        break;
                    }
                    break;
            
                case 'f': {
                    float* val = va_arg(variables, float*);
                    char* token = dequeue(&input_buffer);
                    if (!token) return -1;
                    *val = strtof(token, NULL);
                    break;
                }
            
                case 'c': {
                    char* val = va_arg(variables, char*);
                    char* token = dequeue(&input_buffer);
                    if (!token) return -1;
                    *val = token[0];
                    break;
                }
            
                case 's': {
                    char* val = va_arg(variables, char*);
                    char* token = dequeue(&input_buffer);
                    if (!token) return -1;
                    strcpy(val, token);
                    break;
                }
            }            
            i++; //skip the letter
        }
    }
    va_end(variables);
    return 0;
}

int main(){
    int a;
    my_scanf("%d", &a);
    my_scanf("%d", &a);
    my_scanf("%d", &a);


    return 0;
}
