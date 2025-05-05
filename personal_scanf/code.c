#include <stdio.h>
#include <stdarg.h>
#include <string.h>

typedef struct{
    int length;
    char** buffer;
}string_queue;

//my function
int my_scanf(const char* format, ...){
    //static queue
    static string_queue input_buffer;
    input_buffer.length = 2;
    if(input_buffer.length > 0){
        printf("hello");
    }

    //get the variable variables ready
    va_list variables;
    va_start(variables, format);

    //detect how many inputs we have to format
    int format_count = 0;
    for(int i = 0; i < strlen(format); i++){
        
    }

    va_arg(variables, int);

    va_end(variables);
}

int main(){
    int a;
    int b;
    my_scanf("%d %d", a, b);

    return 0;
}