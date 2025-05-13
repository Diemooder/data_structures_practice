#include <stdio.h>

void swap(int* a, int x, int y){
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

void bubble(int* a, int n){
    int i = n - 1;
    int temp = 0;
    while(i > 0){
        if(a[i] < a[i-1]){
            swap(a, i, i-1);
        }
        i--;
    }
}

void bubble_Sort(int* a, int n){
    int i = 0;
    while(i < n - 1){
        bubble(a, n);
        i++;
    }
}


void display(int* a, int n){
    int i = 0;
    while(i < n){
        printf("%d ", a[i]);
        i++;
    }
    printf("\n");
}

int main(){

    int arr[] = {29, 30, 21, 420, 320, 48l, 23, 1, 3, 200, 489, 532};
    int size = sizeof(arr) / sizeof(int);
    display(arr, size);
    bubble_Sort(arr, size);
    display(arr, size);

    return 0;
}