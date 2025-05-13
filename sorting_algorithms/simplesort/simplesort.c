#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int main(){
    int n;
    int my_array[MAX];
    printf("Enter a number N: ");
    scanf("%d", &n);

    //inputting values at array
    for(int i = 0; i < n; i++){
        my_array[i] = rand() % (5000 + 1);
    }

    //outputting the unsorted array
    for(int i = 0; i < n; i++){
        printf("%d ", my_array[i]);
    }
    printf("\n");

    //sorting an array
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            //Ascending order
            // if(my_array[j] < my_array[i]){
            //     int temp = my_array[i];
            //     my_array[i] = my_array[j];
            //     my_array[j] = temp;
            // }

            //Descending order
            if(my_array[j] > my_array[i]){
                int temp = my_array[i];
                my_array[i] = my_array[j];
                my_array[j] = temp;
            }
        }
    }

    //outputting the sorted array
    for(int i = 0; i < n; i++){
        printf("%d ", my_array[i]);
    }
    
    return 0;
}